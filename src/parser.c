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
 * @file parser.c
 *
 * @brief Process tokens and allocate array of commands to execute.
 */

#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "built-in.h"
#include "utility.h"

/**
 * @brief Used to return on fail in parse().
 */
static const struct AbstractSyntaxTree EMPTY_AST = {NULL, 0};

/**
 * @brief Allocates memory for a new empty node for the AST.
 *
 * @param[in,out] ast The Abstract Syntax Tree.
 *
 * @return True if allocation succeeded, otherwise false.
 */
static bool extend_ast(struct AbstractSyntaxTree* ast) {
    if (!ast) {
        return false;
    }

    ast->nodes = realloc(ast->nodes,
                         (ast->amount + 1) * sizeof(struct Command));
    if (!check_alloc(ast->nodes, "node")) {
        return false;
    }

    struct Command* node = &ast->nodes[ast->amount];

    node->type = UNKNOWN;
    node->name = NULL;
    for (size_t i = 0; i < TOTAL_STREAMS; ++i) {
        node->redirect[i] = NULL;
    }
    node->args = NULL;
    node->args_amount = 0;
    ast->amount++;

    return true;
}

/**
 * @brief Allocates memory for name for Command node and assigns value to it.
 *
 * @param[in,out] node The node to add the name to.
 * @param[in] name The name of the command.
 *
 * @return True if allocation succeeded, otherwise false.
 */
static bool add_name(struct Command* node, const char* name) {
    if (!node) {
        return false;
    }

    node->name = malloc(strlen(name) + 1);
    if (!check_alloc(node->name, "node name")) {
        return false;
    }
    strcpy(node->name, name);
    return true;
}

/**
 * @brief Allocates memory for new argument and assigns value to it.
 *
 * @param[in,out] node The command node to add the argument to.
 * @param[in] arg The argument to add to the command.
 *
 * @return True if allocation succeeded, otherwise false.
 */
static bool add_arg(struct Command* node, const char* arg) {
    node->args = realloc(node->args, (node->args_amount + 1) * sizeof(char*));
    if (!check_alloc(node->args, "node args")) {
        return false;
    }

    if (strlen(arg)) {
        node->args[node->args_amount] = malloc(strlen(arg) + 1);
        if (!check_alloc(node->args[node->args_amount], "node arg")) {
            return false;
        }
        strcpy(node->args[node->args_amount], arg);

    } else {
        node->args[node->args_amount] = NULL;
    }

    node->args_amount++;

    return true;
}

/**
 * @brief Adds a new node to the AST, and initializes it.
 *
 * @param[in,out] ast The Abstract Syntax Tree to add the node to.
 * @param[in] node_name The name of the command to be added.
 *
 * @return A pointer to the new node in AST.
 */
static struct Command* add_node(struct AbstractSyntaxTree* ast,
                                const char* node_name) {
    if (!extend_ast(ast)) {
        return NULL;
    }

    struct Command* node = &ast->nodes[ast->amount - 1];
    if (!add_name(node, node_name) ||
        !add_arg(node, node_name)) {
        return NULL;
    }

    node->type = is_in_table(node->name) ? BUILT_IN : EXTERNAL;

    return node;
}

/**
 * @brief Allocates and sets file path to redirect to for specific stream.
 *
 * @param[in,out] node The command node to add the redirection to.
 * @param[in] file_path The path to the file to redirect to.
 * @param[in] stream_index 0 for stdin, 1 for stdout, 2 for stderr.
 *
 * @return True if allocation succeeded, otherwise false.
 */
static bool add_redirection(struct Command* node,
                            const char* file_path,
                            int stream_index) {
    node->redirect[stream_index] = malloc(strlen(file_path) + 1);
    if (!check_alloc(node->redirect[stream_index], "std stream redirect")) {
        return false;
    }
    strcpy(node->redirect[stream_index], file_path);
    return true;
}

/**
 * @brief Checks if the sequence of nodes is allowed.
 *
 * @details Verify that built-in commands is not used in pipe sequence.
 *
 * @param[in] ast The Abstract Syntax Tree to check.
 *
 * @return True if no built-in commands occurred in pipeline, otherwise false.
 */
static bool is_allowed_sequence(struct AbstractSyntaxTree ast) {
    if (ast.amount > 1 && ast.nodes[0].type == BUILT_IN) {
        return false;
    }
    for (size_t i = 1; i < ast.amount; ++i) {
        if (ast.nodes[i].type == BUILT_IN) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Frees the memory allocated for the Tokens and AbstractSyntaxTree
 * structures.
 *
 * @details Used in exceptional cases in the parse() function.
 *
 * @param[in] tokens The Tokens to free.
 * @param[in] ast The AbstractSyntaxTree to free.
 */
static void free_resources(struct Tokens tokens,
                           struct AbstractSyntaxTree ast) {
    free_tokens(tokens);
    free_ast(ast);
}

struct AbstractSyntaxTree parse(struct Tokens tokens) {
    if (tokens.state != VALID) {
        return EMPTY_AST;
    }

    struct AbstractSyntaxTree ast = {NULL, 0};

    struct Command* node = add_node(&ast, tokens.data[0]);
    if (!node) {
        free_resources(tokens, ast);
        return EMPTY_AST;
    }

    size_t i = 1;
    while (i < tokens.amount) {
        int std_stream = -1;
        if (!strcmp(tokens.data[i], "<")) {
            std_stream = STDIN_FILENO;
        } else if (!strcmp(tokens.data[i], ">")) {
            std_stream = STDOUT_FILENO;
        } else if (!strcmp(tokens.data[i], "2>")) {
            std_stream = STDERR_FILENO;
        }
        if (std_stream != -1) {
            if (++i == tokens.amount ||
                !add_redirection(node, tokens.data[i], std_stream)) {
                free_resources(tokens, ast);
                return EMPTY_AST;
            }

        } else if (!strcmp(tokens.data[i], "|")) {
            // Add NULL as last argument in previous node
            add_arg(node, "");

            if (++i == tokens.amount ||
                !(node = add_node(&ast, tokens.data[i]))) {
                free_resources(tokens, ast);
                return EMPTY_AST;
            }

        } else if (!add_arg(node, tokens.data[i])) {
            free_resources(tokens, ast);
            return EMPTY_AST;
        }
        ++i;
    }
    // Add NULL as last argument in last node
    add_arg(node, "");

    if (!is_allowed_sequence(ast)) {
        printf(BOLD_RED);
        printf("kara: built-in commands are not allowed to use with pipes\n");
        printf(RESET);
        free_resources(tokens, ast);
        return EMPTY_AST;
    }

    free_tokens(tokens);
    return ast;
}

void free_ast(struct AbstractSyntaxTree ast) {
    if (!ast.nodes) {
        return;
    }

    for (size_t i = 0; i < ast.amount; ++i) {
        free(ast.nodes[i].name);

        for (size_t j = 0; j < ast.nodes[i].args_amount; ++j) {
            free(ast.nodes[i].args[j]);
        }
        free(ast.nodes[i].args);

        for (size_t j = 0; j < TOTAL_STREAMS; ++j) {
            free(ast.nodes[i].redirect[j]);
        }
    }

    free(ast.nodes);
}
