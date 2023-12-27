cmake_minimum_required(VERSION 3.28)
project(libimagec C)

set(CMAKE_C_STANDARD 23)

add_library(libimagec
        src/libimagec.c)

target_include_directories(libimagec PUBLIC src)

add_subdirectory(tests)