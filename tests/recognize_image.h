//
// Created by eramoss on 20/01/24.
//

#ifndef LIBIMAGEC_RECOGNIZE_IMAGE_H
#define LIBIMAGEC_RECOGNIZE_IMAGE_H

#include "libimagec.h"
#include "test_utils.h"

#define PNG_IMAGE_PATH TEST_DIRECTORY "test_images/test.png"
#define PNG_ERROR_IMAGE_PATH TEST_DIRECTORY "test_images/test_error.png"

unsigned recognize_png_success() {
    ImageFormat result = image_format(PNG_IMAGE_PATH);
    ASSERT_EQUAL(PNG, result);
    return 0;
};

unsigned recognize_png_error() {
    ImageFormat result = image_format(PNG_ERROR_IMAGE_PATH);
    ASSERT_EQUAL(UNKNOWN, result);
    return 0;
};

unsigned recognize_other_extension_error() {
    ImageFormat result = image_format(TEST_DIRECTORY "recognize_image.h");
    ASSERT_EQUAL(UNKNOWN, result);
    return 0;
};


#define RECOGNIZE_TESTS \
    recognize_png_success,  recognize_png_error,  recognize_other_extension_error

#endif //LIBIMAGEC_RECOGNIZE_IMAGE_H
