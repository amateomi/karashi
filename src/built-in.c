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
 * @file built-in.c
 *
 * @brief Contents shell built-in commands table.
 */

#include "built-in.h"

#include <string.h>

/**
 * @brief Defining the maximum length of a command.
 *
 * @details C programming language forbid to define arrays with two empty
 * square brackets (table[][] is not allowed), so we must determine some
 * arbitrary number to use in TABLE.
 */
#define COMMAND_MAX_LEN 8

/**
 * @brief Table of built-in commands.
 */
static const char TABLE[][COMMAND_MAX_LEN] = {
        CD,
        EXIT
};

bool is_in_table(const char string[]) {
    for (size_t i = 0; i < sizeof(TABLE) / sizeof(char*); ++i) {
        if (!strcmp(string, TABLE[i])) {
            return true;
        }
    }
    return false;
}
