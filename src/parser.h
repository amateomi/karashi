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
 * @file parser.h
 *
 * @brief Tokens parsing and definition of Command and AbstractSyntaxTree
 * structures.
 *
 * @see parser.c
 */

#ifndef KARASHI_PARSER_H
#define KARASHI_PARSER_H

#include "scanner.h"

#define TOTAL_STREAMS 3 ///< Number of standard streams (stdin, stdout, stderr).

/**
 * @brief Type of Command structure.
 */
enum CommandType {
    BUILT_IN, ///< Functionality that is not stored as separate executable.
    EXTERNAL, ///< Executable program that is stored somewhere on drive.
    UNKNOWN, ///<  Represent command with not specified yet type.
};

/**
 * @brief Single command to execute.
 */
struct Command {
    enum CommandType type;         ///< Represent type of Command structure.
    char* name;                    ///< Name of the command.
    char* redirect[TOTAL_STREAMS]; ///< File paths to redirect to.
    char** args;                   ///< Array of command arguments.
    size_t args_amount;            ///< Amount of arguments.
};

/**
 * @brief Array of Command structures, each command is piped to next one.
 */
struct AbstractSyntaxTree {
    struct Command* nodes; ///< Array of Commands.
    size_t amount;         ///< Amount of nodes in array.
};

/**
 * @brief Parses the Tokens and build AbstractSyntaxTree.
 *
 * @param[in] tokens The tokens to parse.
 *
 * @return A struct AbstractSyntaxTree.
 */
struct AbstractSyntaxTree parse(struct Tokens tokens);

/**
 * @brief Frees the memory allocated for the AST.
 *
 * @param[in] ast The AbstractSyntaxTree to free.
 */
void free_ast(struct AbstractSyntaxTree ast);

#endif //KARASHI_PARSER_H
