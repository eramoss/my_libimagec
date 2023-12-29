#ifndef LIBPNG_TESTS
#define LIBPNG_TESTS

#include "test_utils.h"
#include "libimagec.h"

#define IMAGE_TEST_PATH "../../testImage.png"
#define PNG_COLOR_TYPE_RGB2 (6)
#define EXPECTED_DEPTH 8

unsigned read_png_test();


unsigned read_png_test() {
    image *png = read_image(IMAGE_TEST_PATH);

    ASSERT(png->width > 0);
    ASSERT(png->height > 0);
    ASSERT(png->color_type == (PNG_COLOR_TYPE_RGB | PNG_COLOR_TYPE_RGB2));
    ASSERT(png->bit_depth == EXPECTED_DEPTH);

//    default_debug_rgb_(png);
    cleanup_image(png);
    return 0;
}

unsigned png_rgb_to_grayscale_test() {
    image *png = read_image(IMAGE_TEST_PATH);
    FILE *fp = fopen("../../test.png", "wb");;
    png_bytep row = NULL;
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    setjmp(png_jmpbuf(png_ptr));
    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr, png->width, png->height,
                 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    default_png_rgb_to_gray(png->png_ptr, SILENTLY_ACTION);
    png_write_info(png_ptr, info_ptr);
    png_bytep *row_pointers = get_matrix_pointers_RGB(png->png_ptr, png->info_ptr, png->height);
    png_write_rows(png_ptr, row_pointers, png->height);

    png_write_end(png_ptr, info_ptr);
    return 0;
}

#define ALL_LIB_PNG_TESTS \
    read_png_test, png_rgb_to_grayscale_test

#endif
