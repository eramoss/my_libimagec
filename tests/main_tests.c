#include <stdio.h>
#include "recognize_image.h"
#include "libpng_io.h"

typedef unsigned (*TestFunction)();

TestFunction test_suite[] = {
        RECOGNIZE_TESTS, TESTS_LIBPNG_IO,
};

#define NUM_TESTS (sizeof(test_suite) / sizeof(test_suite[0]))

int main() {
    unsigned result = 0;


    for (int i = 0; i < NUM_TESTS; ++i) {
        result += test_suite[i]();
    }

    if (result == 0) {
        printf("All tests passed!\n");
    } else {
        printf("%d tests failed\n", result);
    }

    return (int) result;
}
