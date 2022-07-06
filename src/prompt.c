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
 * @file prompt.c
 *
 * @brief Handle internal logic of what prompt should content.
 */

#include "prompt.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "utility.h"

/**
 * @brief Kara hieroglyph, which is printed instead of default boring Bash "$".
 */
static char KARA[] = BOLD_RED " 殻 " RESET;

/**
 * @brief Used to replace HOME environment variable with "~" in get_prompt().
 */
static const char TILDE[] = "~";

/**
 * @brief Sets the prompt color to a different color each time it's called.
 *
 * @param[in,out] prompt The prompt string to be displayed.
 */
static void set_prompt_color(char prompt[]) {
    static const int RED = 31;
    static const int LAST_COLOR = 37;

    static int COLOR_NUMBER = RED;

    sprintf(prompt, "\033[1;%dm 殻 " RESET, COLOR_NUMBER);

    COLOR_NUMBER++;
    if (COLOR_NUMBER == LAST_COLOR + 1) {
        COLOR_NUMBER = RED;
    }
}

char* get_prompt(void) {
    char* prompt = NULL;

    char* const CWD = getcwd(NULL, 0);
    assert_alloc(CWD, "cwd");

    size_t prompt_length = strlen(CWD) + strlen(KARA) + 1;

    const char* const HOME = check_getenv("HOME");
    bool home_dir = strstr(CWD, HOME) == CWD;
    if (home_dir) {
        prompt_length = prompt_length - strlen(HOME) + strlen(TILDE);
    }

    prompt = malloc(prompt_length);
    assert_alloc(prompt, "prompt");

    if (home_dir) {
        strcpy(prompt, TILDE);
        strcat(prompt, CWD + strlen(HOME));
    } else {
        strcpy(prompt, CWD);
    }

    set_prompt_color(KARA);
    strcat(prompt, KARA);

    free(CWD);
    return prompt;
}
