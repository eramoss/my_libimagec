#ifndef LIBIMAGEC_LIBIMAGEC_H
#define LIBIMAGEC_LIBIMAGEC_H

#include "stdio.h"
#include "stdlib.h"

typedef struct {
    unsigned char *vector_png;
    size_t vector_png_size;
} raw_png_t;

unsigned load_raw_file(raw_png_t *png_handler, const char *filename);

unsigned decompress_png_huffman(raw_png_t *png_handler);


#endif //LIBIMAGEC_LIBIMAGEC_H
