#include <stdio.h>
#include <string.h>
#include "libimagec.h"


// Simple assert macro
#define ASSERT(condition) \
    if (!(condition)) {    \
        printf("Test failed: %s, line %d\n", __FILE__, __LINE__); \
        return 1; \
    }


bool str_contains(const char *haystack, const char *needle) {
    if (haystack == NULL || needle == NULL) {
        return false;
    }
    return strstr(haystack, needle) != NULL;
}

#define PNG_HEADER_SIZE 4

int test_get_raw_png_file() {
    raw_png_t png_handler = {0};
    load_raw_file(&png_handler, "../../testImage.png");
    unsigned char buf[PNG_HEADER_SIZE];
    if (png_handler.vector_png_size > PNG_HEADER_SIZE) {
        for (int i = 0; i < PNG_HEADER_SIZE; i++) {
            buf[i] = png_handler.vector_png[i];
        }
        ASSERT(str_contains(buf, "PNG"));
        return 0;
    }
    return 1;
}

typedef int (*TestFunction)();


TestFunction test_suite[] = {
        test_get_raw_png_file,
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
