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
 * @file scanner.h
 *
 * @brief User input processing and Tokens definition.
 *
 * @see scanner.c
 */

#ifndef KARASHI_SCANNER_H
#define KARASHI_SCANNER_H

#include <stddef.h>

/**
 * @brief State of Tokens structure.
 */
enum TokensState {
    VALID,   ///< Valid Tokens state.
    INVALID, ///< Invalid Tokens state. It is unsafe to use such Tokens.
};

/**
 * @brief Array of tokens.
 *
 * @details Each token represented as C-style string.
 */
struct Tokens {
    enum TokensState state; ///< Represent state of Tokens structure.
    char** data;            ///< Array of tokens.
    size_t amount;          ///< Amount of allocated tokens.
};

/**
 * @brief Takes user input and converts it into tokens.
 *
 * @details Reads a line from the user, tokenizes it, and returns the tokens.
 *
 * @return Tokens struct.
 */
struct Tokens input(void);

/**
 * @brief Frees the memory allocated for the tokens.
 *
 * @param[in] tokens The Tokens to free.
 */
void free_tokens(struct Tokens tokens);

#endif //KARASHI_SCANNER_H
