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
 * @file child.h
 *
 * @brief Provide interface for communication with child processes during pipe
 * handling.
 *
 * @see child.c
 */

#ifndef KARASHI_CHILD_H
#define KARASHI_CHILD_H

#include <stddef.h>
#include <semaphore.h>

extern pid_t child_pid[];   ///< Array of child processes ids.
extern size_t child_amount; ///< Amount of current child processes.

extern sem_t* sem;      ///< Used for child sync during pipes handling.
extern char sem_name[]; ///< Unique semaphore name.

/**
 * @brief Creates a semaphore name based on the shell process ID.
 */
void set_sem_name(void);

/**
 * @brief Sends a signal to all the child processes.
 *
 * @param[in] sig The signal to send to the child processes.
 */
void send_signal_to_child(int sig);

/**
 * @brief Force termination of all child processes if any and close semaphore.
 */
void clear_child(void);

#endif //KARASHI_CHILD_H
