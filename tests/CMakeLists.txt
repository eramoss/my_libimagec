add_executable(tests
        get_raw_bytes.c)
target_link_libraries(tests PRIVATE libimagec)

target_include_directories(tests PRIVATE ../src)