add_executable(tests
        main_tests.c
        test_utils.h
        recognize_image.h
)
target_link_libraries(tests PRIVATE libimagec)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")
target_include_directories(tests PRIVATE ../include)