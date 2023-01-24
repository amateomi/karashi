/****************************************************************************
 * Copyright (c) 2023 Andrey Sikorin.                                       *
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

#pragma once

#include <string>
#include <string_view>
#include <vector>

class Token {
public:
    enum class Type {
        INPUT_REDIRECTION = 0b100,
        OUTPUT_REDIRECTION = 0b101,
        ERROR_REDIRECTION = 0b110,
        PIPE = 0b001,
        WORD = 0b010,
    };

    class WordException : public std::exception {
    public:
        [[nodiscard]] const char* what() const noexcept override
        {
            return "Word string only allowed for Token::Type::WORD";
        }
    };

    explicit Token(Type type) noexcept;
    Token(Type type, std::string word);

    [[nodiscard]] Type GetType() const noexcept;
    [[nodiscard]] const std::string& GetWord() const;

private:
    Type m_Type;
    std::string m_Word; ///< Store string for WORD type
};

[[nodiscard]] std::vector<Token> tokenize(std::string_view command) noexcept;
