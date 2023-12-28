//
// Created by eramoss on 28/12/23.
//

#ifndef LIBIMAGEC_ALLOC_UTILS_H
#define LIBIMAGEC_ALLOC_UTILS_H

#include <stdio.h>
#include <stdlib.h>


static inline void check_alloc(void *p) {
    if (p == NULL) {
        puts("Memory allocation error.");
        exit(EXIT_FAILURE);
    }
}


#endif //LIBIMAGEC_ALLOC_UTILS_H
