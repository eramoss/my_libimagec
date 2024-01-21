//
// Created by eramoss on 20/01/24.
//

#ifndef LIBIMAGEC_LIBPNG_IO_H
#define LIBIMAGEC_LIBPNG_IO_H

#include "test_utils.h"

unsigned read_png_success() {
    Image *image = load_image(PNG_IMAGE_PATH);
    ASSERT_EQUAL(PNG, image->format);
    ASSERT_EQUAL(499, image->height);
    ASSERT_EQUAL(730, image->width);
    return 0;
}

unsigned copy_png() {
    Image *image = load_image(PNG_IMAGE_PATH);
    save_image(TEST_DIRECTORY"test_images/copy_test.png", image);
    Image *copy = load_image(TEST_DIRECTORY"test_images/copy_test.png");
    for (size_t i = 0; i < 499; i++) {
        for (size_t j = 0; j < 730; j++) {
            ASSERT_EQUAL(copy->data[i * j], image->data[i * j]);
        }
    }
    return 0;
}


#define TESTS_LIBPNG_IO \
    read_png_success, copy_png
#endif //LIBIMAGEC_LIBPNG_IO_H
