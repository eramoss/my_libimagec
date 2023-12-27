cmake_minimum_required(VERSION 3.28)
project(libimagec C)

set(CMAKE_C_STANDARD 23)

add_library(libimagec
        src/libimagec.c)

target_include_directories(libimagec PRIVATE include)
target_include_directories(libimagec PUBLIC lib)

target_link_libraries(libimagec PRIVATE png)

add_subdirectory(lib/libpng-1.6.40)
add_subdirectory(tests)
