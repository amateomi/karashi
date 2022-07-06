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
 * @file utility.h
 *
 * @brief Provide functions for error handling and macros for colored output.
 *
 * @see utility.c
 */

#ifndef KARASHI_UTILITY_H
#define KARASHI_UTILITY_H

#include <stdbool.h>

#define BOLD_RED "\033[1;31m" ///< Used to print text in red.
#define RESET    "\033[0m"    ///< Used to reset terminal text color to default.

/**
 * @brief If the pointer is null, print an error message.
 *
 * @param[in] ptr The pointer to check.
 * @param[in] msg End of the message to print when ptr is NULL.
 *
 * @return False when ptr is NULL, otherwise true.
 */
bool check_alloc(const void* ptr, const char msg[]);

/**
 * @brief If the pointer is null, print an error message and exit.
 *
 * @param[in] ptr The pointer to check.
 * @param[in] msg End of the message to print when ptr is NULL.
 */
void assert_alloc(const void* ptr, const char msg[]);

/**
 * @brief Get environment variable value with validation.
 *
 * @details Wrapper for getenv(). Checks if the environment variable is set,
 * and if it is not, prints an error message and exits the program.
 *
 * @param[in] env_var The name of the environment variable to check.
 *
 * @return The value of the environment variable.
 */
char* check_getenv(const char* env_var);

/**
 * @brief Prints `errno` error message in bold red.
 */
void print_errno(void);

#endif //KARASHI_UTILITY_H
