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
 * @file built-in.h
 *
 * @brief Contents all built-in shell commands.
 *
 * @see built-in.c
 */

#ifndef KARASHI_BUILT_IN_H
#define KARASHI_BUILT_IN_H

#include <stdbool.h>

// Shell built-in commands
#define CD "cd"     ///< Change current working directory.
#define EXIT "exit" ///< Quit shell.

/**
 * @brief Determine if string is built-in command.
 *
 * @param[in] string The string to check.
 *
 * @return True if the string is in the table, and false otherwise.
 */
bool is_in_table(const char string[]);

#endif //KARASHI_BUILT_IN_H
