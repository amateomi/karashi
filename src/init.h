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
 * @file init.h
 *
 * @brief Configuration of the Kara shell.
 *
 * @see init.c
 */

#ifndef KARASHI_INIT_H
#define KARASHI_INIT_H

/**
 * @brief Initialize shell.
 *
 * @details Sets up the signal handlers and the atexit function.
 */
void init(void);

#endif //KARASHI_INIT_H
