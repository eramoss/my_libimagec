//
// Created by eramoss on 28/12/23.
//

#ifndef LIBIMAGEC_TEST_UTILS_H
#define LIBIMAGEC_TEST_UTILS_H

#include "libimagec.h"

#define TEST_DIRECTORY "../../tests/"
#define PNG_IMAGE_PATH TEST_DIRECTORY "test_images/test.png"
#define PNG_ERROR_IMAGE_PATH TEST_DIRECTORY "test_images/test_error.png"
// Simple ASSERTs macro
#define ASSERT(condition) \
    do { \
        if (!(condition)) { \
            printf("Test failed: %s, line %d\n", __FILE__, __LINE__); \
            return 1; \
        } \
    } while (0)

#define ASSERT_EQUAL(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("Test failed: %s, line %d - Expected: %d, Actual: %d\n", \
                __FILE__, __LINE__, (expected), (actual)); \
            return 1; \
        } \
    } while (0)

#define ASSERT_STRING_EQUAL(expected, actual) \
    do { \
        if (strcmp((expected), (actual)) != 0) { \
            printf("Test failed: %s, line %d - Expected: \"%s\", Actual: \"%s\"\n", \
                __FILE__, __LINE__, (expected), (actual)); \
            return 1; \
        } \
    } while (0)

#endif //LIBIMAGEC_TEST_UTILS_H

