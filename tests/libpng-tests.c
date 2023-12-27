#include <stdio.h>
#include <string.h>
#include "libimagec.h"


// Simple assert macro
#define ASSERT(condition) \
    if (!(condition)) {    \
        printf("Test failed: %s, line %d\n", __FILE__, __LINE__); \
        return 1; \
    }

unsigned read_png_test() {
    read_png_file("../../testImage.png");
    return 0;
}

typedef unsigned (*TestFunction)();


TestFunction test_suite[] = {
        read_png_test,
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
