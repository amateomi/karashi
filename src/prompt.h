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
 * @file prompt.h
 *
 * @brief Provide shell front-end prompt.
 *
 * @see prompt.c
 */

#ifndef KARASHI_PROMPT_H
#define KARASHI_PROMPT_H

/**
 * @brief Generate prompt represented as C-style string.
 *
 * @details Substitute path read from HOME environment variable with "~" symbol.
 *
 * @return Shell prompt.
 */
char* get_prompt(void);

#endif //KARASHI_PROMPT_H
