#include <stdio.h>
#include <string.h>
#include "libimagec.h"


// Simple assert macro
#define ASSERT(condition) \
    if (!(condition)) {    \
        printf("Test failed: %s, line %d\n", __FILE__, __LINE__); \
        return 1; \
    }

void debug_png(png_image *image) {
    printf("PNG Image Information:\n");
    printf("Width: %d\n", image->width);
    printf("Height: %d\n", image->height);
    printf("Format: %d\n", image->format);
    printf("Color Map Entries: %d\n", image->colormap_entries);
    printf("Flags: %d\n", image->flags);
    printf("Message: %s\n", image->message);
}

int read_png_test() {
    png_image *image = create_png_structure();
    read_png(image, "../../testImage.png");
    debug_png(image);
    ASSERT(strcmp(image->message, "") == 0);
    return 0;
}

typedef int (*TestFunction)();


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
