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
 * @file utility.c
 *
 * @brief Implementation for error handling functions.
 */

#include "utility.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

bool check_alloc(const void* ptr, const char msg[]) {
    if (!ptr) {
        printf(BOLD_RED);
        printf("kara: failed to allocate %s\n", msg);
        printf(RESET);
        return false;
    }
    return true;
}

void assert_alloc(const void* ptr, const char msg[]) {
    if (!ptr) {
        printf(BOLD_RED);
        printf("kara: failed to allocate %s\n", msg);
        printf(RESET);
        exit(EXIT_FAILURE);
    }
}

char* check_getenv(const char* env_var) {
    char* value = getenv(env_var);
    if (!value) {
        printf(BOLD_RED);
        printf("Something strange happened in your system:"
               " %s variable is missing!\n", env_var);
        printf(RESET);
        exit(EXIT_FAILURE);
    }
    return value;
}

void print_errno(void) {
    printf(BOLD_RED);
    printf("kara: %s\n", strerror(errno));
    printf(RESET);
}
