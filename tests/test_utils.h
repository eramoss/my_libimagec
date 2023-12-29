//
// Created by eramoss on 28/12/23.
//

#ifndef LIBIMAGEC_TEST_UTILS_H
#define LIBIMAGEC_TEST_UTILS_H

#include "libimagec.h"
// Simple ASSERT macro
#define ASSERT(condition) \
    if (!(condition)) {    \
        printf("Test failed: %s, line %d\n", __FILE__, __LINE__); \
        return 1; \
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

void default_debug_rgb_(image *png) {
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

}


#endif //LIBIMAGEC_TEST_UTILS_H

