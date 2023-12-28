add_executable(tests
        libpng-tests.h
        matrix_tests.h
        main_tests.c
        test_utils.h
)
target_link_libraries(tests PRIVATE libimagec)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
target_include_directories(tests PRIVATE ../include)