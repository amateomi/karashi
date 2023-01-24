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

#include "shell.hpp"

#include <iostream>

#include "token.hpp"

Shell::Shell(int argc, char** argv) noexcept
{
    m_Args.reserve(argc);
    for (int i = 1; i < argc; ++i) {
        m_Args.emplace_back(argv[i]);
    }
}

void Shell::Run() const noexcept
{
    try {
        m_Args.empty() ? RunInteractive() : RunScript();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

[[noreturn]] void Shell::RunInteractive() const
{
    while (true) {
        std::cout << "@ ";
        std::string input;
        std::getline(std::cin, input);
        auto tokens = tokenize(input);
        for (const auto& item : tokens) {
            switch (item.GetType()) {
            case Token::Type::INPUT_REDIRECTION:
                std::cout << "INPUT_REDIRECTION" << std::endl;
                break;

            case Token::Type::OUTPUT_REDIRECTION:
                std::cout << "OUTPUT_REDIRECTION" << std::endl;
                break;

            case Token::Type::ERROR_REDIRECTION:
                std::cout << "ERROR_REDIRECTION" << std::endl;
                break;

            case Token::Type::PIPE:
                std::cout << "PIPE" << std::endl;
                break;

            case Token::Type::WORD:
                std::cout << "WORD " << item.GetWord() << std::endl;
                break;
            }
        }
    }
}

void Shell::RunScript() const { }
