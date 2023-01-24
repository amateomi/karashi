cmake_minimum_required(VERSION 3.24)

project(sheru
        VERSION 0.2.0
        DESCRIPTION "Linux Shell"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_executable(${PROJECT_NAME} src/main.cpp src/shell.hpp src/shell.cpp src/token.cpp src/token.hpp)
