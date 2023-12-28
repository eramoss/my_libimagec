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
    //    optimize_dip_depth_color_type(png, color_type, bit_depth);
    png_bytep *row_pointers = get_matrix_pointers_RGB(png, height);

#ifdef DEBUG
    debug_rgb_values(width, height, row_pointers);
#endif

    /*
     cleanup section
     */
    cleanup_png(png);
    for (int y = 0; y < height; y++)
        free(row_pointers[y]);
    free(row_pointers);
    return 0;
}

unsigned test_rgb_matrix() {
    png_infos *png = read_png_file(IMAGE_TEST_PATH);
    png_uint_32 width = png_get_image_width(*png->png_ptr, *png->info_ptr);
    png_uint_32 height = png_get_image_height(*png->png_ptr, *png->info_ptr);

    ASSERT(width > 0);
    ASSERT(height > 0);

    png_bytep *row_pointers = get_matrix_pointers_RGB(png, height);
    matrix *m = row_pointers2matrix(width, height, row_pointers);
    ASSERT(matrix_x(m) == width);
    ASSERT(matrix_y(m) == height);
#if DEBUG
    rgb_struct_t *rgb_value = matrix_get(m, m->x - 1, m->y - 1);
    printf("matrix point:(%d, %d) [%d,%d,%d]\n", m->x - 1, m->y - 1, rgb_value->red, rgb_value->green, rgb_value->blue);
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
    read_png_test, test_rgb_matrix

#endif
