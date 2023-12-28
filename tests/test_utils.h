//
// Created by eramoss on 28/12/23.
//

#ifndef LIBIMAGEC_TEST_UTILS_H
#define LIBIMAGEC_TEST_UTILS_H
// Simple ASSERT macro
#define ASSERT(condition) \
    if (!(condition)) {    \
        printf("Test failed: %s, line %d\n", __FILE__, __LINE__); \
        return 1; \
    }
#endif //LIBIMAGEC_TEST_UTILS_H
