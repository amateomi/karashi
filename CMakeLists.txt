cmake_minimum_required(VERSION 3.24)

project(sheru
        VERSION 0.2.0
        DESCRIPTION "Linux Shell"
        HOMEPAGE_URL "https://github.com/amateomi/karashi"
        LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(SetupCxx)

add_subdirectory(src)
