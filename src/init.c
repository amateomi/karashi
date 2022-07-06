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
 * @file init.c
 *
 * @brief Configure atexit handler and signals redirection to child.
 */

#include "init.h"

#include <stdlib.h>
#include <signal.h>

#include <unistd.h>

#include "child.h"

/**
 * @brief A global variable that is used to store the pid of the process.
 *
 * @details Helps to prevent recursive calls in signal_handler().
 */
static pid_t KARA_PID;

/**
 * @brief Redirect signal from shell to current running child processes.
 *
 * @details If the signal is sent to the parent process, send it to the child
 * process. If the signal is sent to the child process, discard handler and
 * raise sig.
 *
 * @param[in] sig The signal number.
 */
static void signal_handler(int sig) {
    if (getpid() == KARA_PID) {
        send_signal_to_child(sig);
    } else {
        signal(sig, SIG_DFL);
        raise(sig);
    }
}

void init(void) {
    KARA_PID = getpid();
    set_sem_name();

    signal(SIGINT, signal_handler);
    signal(SIGQUIT, signal_handler);
    signal(SIGTSTP, signal_handler);
    signal(SIGSTOP, signal_handler);
    signal(SIGCONT, signal_handler);

    atexit(clear_child);
}
