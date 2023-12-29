#ifndef LIBPNG_TESTS
#define LIBPNG_TESTS

#include "test_utils.h"
#include "libimagec.h"

#define IMAGE_TEST_PATH "../../testImage.png"
#define PNG_COLOR_TYPE_RGB2 (6)
#define EXPECTED_DEPTH 8


unsigned read_png_test();

unsigned test_rgb_matrix();

void debug_rgb_values(png_uint_32 width, png_uint_32 height, png_bytep const *row_pointers);

unsigned read_png_test() {
    image *png = read_image(IMAGE_TEST_PATH);

    ASSERT(png->width > 0);
    ASSERT(png->height > 0);
    ASSERT(png->color_type == (PNG_COLOR_TYPE_RGB | PNG_COLOR_TYPE_RGB2));
    ASSERT(png->bit_depth == EXPECTED_DEPTH);


#ifdef DEBUG
    png_bytep *row_pointers = get_matrix_pointers_RGB(png->png_ptr, png->info_ptr, png->height);
    debug_rgb_values(png->width, png->height, row_pointers);
    /*
     cleanup section
 */
    cleanup_image(png);
    for (int y = 0; y < png->height; y++)
        free(row_pointers[y]);
    free(row_pointers);
#endif


    return 0;
}

/*
 * ----------------------------------------------
 *
 *
 *         UTILS SECTION FOR TESTING
 *
 *
 * ---------------------------------------------
 */


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


#define ALL_LIB_PNG_TESTS \
    read_png_test

#endif
