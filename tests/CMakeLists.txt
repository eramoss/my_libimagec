add_executable(tests
        libpng-tests.c)
target_link_libraries(tests PRIVATE libimagec)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
target_include_directories(tests PRIVATE ../include)