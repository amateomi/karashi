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
 * @file child.c
 *
 * @brief Contents unique shell semaphore and array for child processes ids.
 */

#include "child.h"

#include <stdio.h>
#include <signal.h>

#include <unistd.h>

#include "utility.h"

#define MAX_CHILD 1024 ///< Max amount of commands in pipe queue
#define MAX_LEN 16     ///< Max length for unique semaphore name

pid_t child_pid[MAX_CHILD];
size_t child_amount;

sem_t* sem;
char sem_name[MAX_LEN];

void set_sem_name(void) {
    sprintf(sem_name, "kara.%d", getpid());
}

void send_signal_to_child(int sig) {
    for (size_t i = 0; i < child_amount; ++i) {
        if (child_pid[i] && kill(child_pid[i], sig)) {
            print_errno();
        }
    }
}

void clear_child(void) {
    send_signal_to_child(SIGTERM);
    child_amount = 0;
    sem_close(sem);
    sem_unlink(sem_name);
}
