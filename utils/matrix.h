//
// Created by eramoss on 28/12/23.
//

#ifndef LIBIMAGEC_MATRIX_H
#define LIBIMAGEC_MATRIX_H

#include "alloc_utils.h"
#include "stdlib.h"

typedef void *data_type;
typedef struct {
    int x;
    int y;
    data_type **data;
} matrix;

matrix *create_matrix(int x, int y);

unsigned matrix_free(matrix *);

data_type *matrix_get(matrix *, int x, int y);

#define matrix_set_(matrix, i, j, value) matrix_set(matrix, i, j, (void*)(value))

unsigned matrix_set(matrix *matrix, int i, int j, data_type v);

unsigned matrix_x(matrix *matrix);

unsigned matrix_y(matrix *matrix);


#endif //LIBIMAGEC_MATRIX_H
