//
// Created by eramoss on 20/01/24.
//

#ifndef LIBIMAGEC_FILES_H
#define LIBIMAGEC_FILES_H

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

FILE *fopen_read_bytes(const char *file_path) {
    FILE *fp = fopen(file_path, "rb");
    if (!fp) {
        fprintf(stderr, "Error: Unable to open file for read bytes %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    return fp;
}

FILE *fopen_read(const char *file_path) {
    FILE *fp = fopen(file_path, "r");
    if (!fp) {
        fprintf(stderr, "Error: Unable to open file for read %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    return fp;
}

FILE *fopen_write(const char *file_path) {
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file for write %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE *fopen_write_bytes(const char *file_path) {
    FILE *file = fopen(file_path, "wb");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file for writing bytes %s\n", file_path);
        exit(EXIT_FAILURE);
    }
    return file;
}


#endif //LIBIMAGEC_FILES_H
