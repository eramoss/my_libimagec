add_executable(tests
        libpng-tests.c)
target_link_libraries(tests PRIVATE libimagec)

target_include_directories(tests PRIVATE ../include)