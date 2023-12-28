#include <stdio.h>
#include "libpng-tests.h"
#include "matrix_tests.h"


typedef unsigned (*TestFunction)();

TestFunction test_suite[] = {
        ALL_LIB_PNG_TESTS,
        ALL_MATRIX_TESTS,
};

#define NUM_TESTS (sizeof(test_suite) / sizeof(test_suite[0]))

int main() {
    int result = 0;


    for (int i = 0; i < NUM_TESTS; ++i) {
        result += test_suite[i]();
    }

    if (result == 0) {
        printf("All tests passed!\n");
    } else {
        printf("%d tests failed\n", result);
    }

    return result;
}
