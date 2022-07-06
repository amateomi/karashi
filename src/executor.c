/****************************************************************************
 * Copyright (c) 2022 Andrey Sikorin.                                       *
 *                                                                          *
 * This program is free software: you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by     *
 * the Free Software Foundation, version 3.                                 *
 *                                                                          *
 * This program is distributed in the hope that it will be useful, but      *
 * WITHOUT ANY WARRANTY; without even the implied warranty of               *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU         *
 * General Public License for more details.                                 *
 *                                                                          *
 * You should have received a copy of the GNU General Public License        *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.     *
 ****************************************************************************/

/**
 * @file executor.c
 *
 * @brief Analyze AbstractSyntaxTree, handle I/O redirections and pipes.
 */

#include "executor.h"

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/wait.h>
#include <fcntl.h>

#include "built-in.h"
#include "child.h"
#include "utility.h"

/**
 * @brief Executes shell built-in commands whose declared in built-in.h.
 *
 * @param[in] command The command to execute.
 */
static void execute_builtin_command(struct Command* command) {
    if (!strcmp(command->name, CD) && command->args) {
        if (chdir(command->args[1])) {
            print_errno();
        }
    } else if (!strcmp(command->name, EXIT)) {
        exit(EXIT_SUCCESS);
    }
}

/**
 * @brief Redirects stdin, stdout and stderr if needed.
 *
 * @details Called in child_process_handler().
 *
 * @param[in] command The command to execute.
 */
static void setup_std_streams(const struct Command* command) {
    for (int i = 0; i < 3; ++i) {
        if (command->redirect[i]) {
            int fd = open(command->redirect[i],
                          O_RDWR | O_CREAT,
                          S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

            if (fd < 0 || dup2(fd, i) < 0) {
                print_errno();
                exit(errno);
            }
        }
    }
}

/**
 * @brief Called after fork in child process in execute_external_command().
 *
 * @details Sets up the child process's standard streams, waits until it's its
 * turn to execute, and then execute.
 *
 * @param[in] command The command to execute
 * @param[in] id The id of the process (not pid). This is used to determine
 * execution order during pipe handling.
 * @param[in] write_pipe The file descriptor of the write end of the pipe.
 * @param[in] read_pipe The file descriptor of the read end of the pipe.
 */
static void child_process_handler(const struct Command* command, int id,
                                  int write_pipe, int read_pipe) {
    setup_std_streams(command);

    if (write_pipe != -1 && dup2(write_pipe, STDOUT_FILENO) == -1) {
        exit(errno);
    }
    if (read_pipe != -1 && dup2(read_pipe, STDIN_FILENO) == -1) {
        exit(errno);
    }

    // Wait until our turn to exec
    int value = 0;
    do {
        sem_getvalue(sem, &value);
    } while (value != id);
    sem_wait(sem);

    sem_unlink(sem_name);
    execvp(command->name, command->args);
    abort();
}

/**
 * @brief Execute sequence of programs whose is stored on drive.
 *
 * @details Algorithm:
 * 1. Create n-1 pipes, when n is amount of commands
 * 2. Create semaphore for synchronization parent and child process
 * 3. Fork n child processes. In each child process setup redirections and pipes
 * 4. Start child process execution
 * 5. Close all pipes in shell process
 * 6. Wait for child process exit
 *
 * @param[in] ast The AbstractSyntaxTree to execute.
 */
static void execute_external_command(struct AbstractSyntaxTree ast) {
    // Create n-1 pipes, when n is amount of commands
    const size_t PIPE_SIZE = ast.amount - 1;
    int pipes[PIPE_SIZE][2];

    for (size_t i = 0; i < PIPE_SIZE; ++i) {
        if (pipe2(pipes[i], O_CLOEXEC)) {
            print_errno();
            return;
        }
    }

    // Create semaphore for synchronization parent and child process
    sem = sem_open(sem_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR, 1);
    if (sem == SEM_FAILED) {
        print_errno();
        return;
    }

    // Fork n child processes. In each child process setup redirections and pipes
    for (size_t i = 0; i < ast.amount; ++i) {
        sem_post(sem);
        child_pid[child_amount] = fork();
        if (child_pid[child_amount] < 0) {
            print_errno();
            return;
        } else if (child_pid[child_amount]) { // Parent process
            ++child_amount;
        } else { // Child process
            int write_pipe = (i == ast.amount - 1) ? -1 : pipes[i][1];
            int read_pipe = (i == 0) ? -1 : pipes[i - 1][0];
            child_process_handler(&ast.nodes[i], (int) i + 1,
                                  write_pipe, read_pipe);
        }
    }

    // Start child process execution
    sem_wait(sem);

    // Close all pipes in main kara process
    for (size_t i = 0; i < PIPE_SIZE; ++i) {
        if (close(pipes[i][0]) || close(pipes[i][1])) {
            print_errno();
            return;
        }
    }

    // Wait for child process exit
    int status;
    for (size_t i = 0; i < ast.amount; ++i) {
        if (waitpid(child_pid[i], &status, 0) < 0) {
            print_errno();
            return;
        }
        child_pid[i] = 0;
    }
    if (!WIFEXITED(status)) {
        printf(BOLD_RED "kara: failed to run %s" RESET "\n",
               ast.nodes[ast.amount - 1].name);

    } else if (status) {
        printf(BOLD_RED "%s exit status %d" RESET "\n",
               ast.nodes[ast.amount - 1].name, status);
    }
}

void execute(struct AbstractSyntaxTree ast) {
    if (!ast.nodes) {
        return;
    }
    struct Command* command = &ast.nodes[0];
    switch (command->type) {
        case UNKNOWN:
            break;

        case BUILT_IN:
            execute_builtin_command(command);
            break;

        case EXTERNAL:
            execute_external_command(ast);
            clear_child();
            break;
    }
    free_ast(ast);
}
