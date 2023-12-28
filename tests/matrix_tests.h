//
// Created by eramoss on 28/12/23.
//

#ifndef MATRIX_TESTS
#define MATRIX_TESTS

#include "../utils/matrix.h"
#include "test_utils.h"


unsigned test_create_matrix() {
    matrix *m = create_matrix(3, 4);

    // Check matrix dimensions
    ASSERT(matrix_x(m) == 3 && matrix_y(m) == 4);

    // Check all values are initially NULL
    for (int i = 0; i < matrix_x(m) - 1; i++) {
        for (int j = 0; j < matrix_y(m) - 1; j++) {
            ASSERT(matrix_get(m, i, j) == NULL);
        }
    }

    matrix_free(m);
    return 0;
}

unsigned test_matrix_set_and_get() {
    matrix *m = create_matrix(2, 2);

    // Set values
    matrix_set_(m, 0, 0, 1);
    matrix_set_(m, 0, 1, 2);
    matrix_set_(m, 1, 0, 3);
    matrix_set_(m, 1, 1, 4);

    // Check values
    ASSERT(matrix_get(m, 0, 0) == 1);
    ASSERT(matrix_get(m, 0, 1) == 2);
    ASSERT(matrix_get(m, 1, 0) == 3);
    ASSERT(matrix_get(m, 1, 1) == 4);

    matrix_free(m);
    return 0;
}


#define ALL_MATRIX_TESTS \
    test_create_matrix , test_matrix_set_and_get

#endif