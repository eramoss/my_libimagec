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

    default_debug_rgb_(png);
    return 0;
}

#define ALL_LIB_PNG_TESTS \
    read_png_test

#endif
