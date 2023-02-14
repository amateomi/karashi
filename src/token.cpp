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

#include "token.hpp"

#include <algorithm>
#include <regex>

Token::Token(Token::Type type) noexcept
    : m_Type { type }
{
}

Token::Token(Token::Type type, std::string word)
    : m_Type { type }
    , m_Word { std::move(word) }
{
    if (m_Type != Type::WORD) {
        throw WordException {};
    }
}

Token::Type Token::GetType() const noexcept { return m_Type; }

const std::string& Token::GetWord() const
{
    if (m_Type != Type::WORD) {
        throw WordException {};
    }
    return m_Word;
}

std::vector<Token> tokenize(std::string_view command) noexcept
{
    // Match words separated by whitespaces and text enclosed in quotes
    const std::regex re { "[^\\s\"']+|\"([^\"]*)\"|'([^']*)'" };
    const auto begin = std::regex_token_iterator { command.begin(), command.end(), re };
    const auto end = std::cregex_token_iterator {};
    std::vector<Token> result;
    std::for_each(begin, end, [&result](const auto& match) {
        if (match == "<") {
            result.emplace_back(Token::Type::INPUT_REDIRECTION);

        } else if (match == ">") {
            result.emplace_back(Token::Type::OUTPUT_REDIRECTION);

        } else if (match == "2>") {
            result.emplace_back(Token::Type::ERROR_REDIRECTION);

        } else if (match == "|") {
            result.emplace_back(Token::Type::PIPE);

        } else {
            std::string word { match };
            const bool isQuoted = word.front() == '"' || word.front() == '\'';
            if (isQuoted) {
                word = word.substr(1, word.length() - 2);
            }
            if (!word.empty()) {
                result.emplace_back(Token::Type::WORD, word);
            }
        }
    });
    return result;
}
