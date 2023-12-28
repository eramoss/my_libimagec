//
// Created by eramoss on 28/12/23.
//

#include "matrix.h"
#include "assert.h"

matrix *create_matrix(int x, int y) {
    matrix *m = malloc(sizeof(matrix));
    check_alloc(m);
    m->x = x;
    m->y = y;
    m->data = malloc(sizeof(void *) * m->x);
    check_alloc(m->data);

    for (int i = 0; i < m->x; i++) {
        m->data[i] = calloc(m->y, sizeof(void *));
        check_alloc(m->data[i]);
    }

    return m;
}

unsigned matrix_free(matrix *matrix) {
    int x = matrix->x;
    for (int i = 0; i < x; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
    return 0;
}


data_type *matrix_get(matrix *matrix, int i, int j) {
    assert(i >= 0 && i < matrix->x);
    assert(j >= 0 && j < matrix->y);

    return matrix->data[i][j];
}


unsigned matrix_set(matrix *matrix, int i, int j, void *v) {
    assert(i >= 0 && i < matrix->x);
    assert(j >= 0 && j < matrix->y);

    matrix->data[i][j] = v;
    return 0;
}


unsigned matrix_x(matrix *matrix) {
    return matrix->x;
}


unsigned matrix_y(matrix *matrix) {
    return matrix->y;
}