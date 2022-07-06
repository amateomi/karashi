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
 * @file executor.h
 *
 * @brief Execute AbstractSyntaxTree.
 *
 * @see executor.c
 */

#ifndef KARASHI_EXECUTOR_H
#define KARASHI_EXECUTOR_H

#include "parser.h"

/**
 * @brief Executes AbstractSyntaxTree.
 *
 * @param[in] ast The AbstractSyntaxTree to execute.
 */
void execute(struct AbstractSyntaxTree ast);

#endif //KARASHI_EXECUTOR_H
