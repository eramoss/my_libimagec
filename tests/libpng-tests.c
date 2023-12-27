#include <stdio.h>
#include <string.h>
#include "libimagec.h"

#define IMAGE_TEST_PATH "../../testImage.png"
#define PNG_COLOR_TYPE_RGB2 (6)
#define EXPECTED_DEPTH 8


// Simple ASSERT macro
#define ASSERT(condition) \
    if (!(condition)) {    \
        printf("Test failed: %s, line %d\n", __FILE__, __LINE__); \
        return 1; \
    }

void optimize_dip_depth_color_type(const png_infos *png, png_byte color_type, png_byte bit_depth);

png_bytep *get_matrix_pointers_RGB(const png_infos *png, png_uint_32 height);

void debug_rgb_values(png_uint_32 width, png_uint_32 height, png_bytep const *row_pointers);

unsigned read_png_test() {
    png_infos *png = read_png_file(IMAGE_TEST_PATH);
    png_uint_32 width = png_get_image_width(*png->png_ptr, *png->info_ptr);
    png_uint_32 height = png_get_image_height(*png->png_ptr, *png->info_ptr);
    png_byte color_type = png_get_color_type(*png->png_ptr, *png->info_ptr);
    png_byte bit_depth = png_get_bit_depth(*png->png_ptr, *png->info_ptr);

    ASSERT(width > 0);
    ASSERT(height > 0);
    ASSERT(color_type == (PNG_COLOR_TYPE_RGB | PNG_COLOR_TYPE_RGB2));
    ASSERT(bit_depth == EXPECTED_DEPTH);


    //  Optional
    optimize_dip_depth_color_type(png, color_type, bit_depth);

    png_bytep *row_pointers = get_matrix_pointers_RGB(png, height);

    cleanup_png(png);
#ifdef DEBUG
    debug_rgb_values(width, height, row_pointers);

    for (int y = 0; y < height; y++)
        free(row_pointers[y]);
    free(row_pointers);
#endif
    return 0;
}

void debug_rgb_values(png_uint_32 width, png_uint_32 height,
                      png_bytep const *row_pointers) {// Access RGB values for each pixel
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width * 3; x += 3) {
            png_byte red = row_pointers[y][x];
            png_byte green = row_pointers[y][x + 1];
            png_byte blue = row_pointers[y][x + 2];

            // For debugging, you can print the RGB values
            printf("Pixel at (%d, %d) - Red: %d, Green: %d, Blue: %d\n", x / 3, y, red, green, blue);
        }
    }
}

png_bytep *get_matrix_pointers_RGB(const png_infos *png, png_uint_32 height) {
    png_bytep *row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++)
        row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(*png->png_ptr, *png->info_ptr));

    png_read_image(*png->png_ptr, row_pointers);
    return row_pointers;
}

void optimize_dip_depth_color_type(const png_infos *png, png_byte color_type, png_byte bit_depth) {
    if (bit_depth == 1 || bit_depth == 2 || bit_depth == 4)
        png_set_expand(*png->png_ptr);


    if (bit_depth == 16)
        png_set_strip_16(*png->png_ptr);


    if (color_type == PNG_COLOR_TYPE_RGBA)
        png_set_strip_alpha(*png->png_ptr);
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
