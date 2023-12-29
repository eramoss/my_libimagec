#ifndef LIBIMAGEC_LIBIMAGEC_H
#define LIBIMAGEC_LIBIMAGEC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <zlib.h>
#include "../lib/libpng-1.6.40/png.h"

typedef unsigned char image_byte;
typedef unsigned short image_uint_16;
typedef image_uint_16 image_type;

typedef struct {
    png_structp *png_ptr;
    png_infop *info_ptr;
    image_uint_16 width;
    image_uint_16 height;
    image_byte bit_depth;
    image_byte color_type;
    image_byte channels;
    image_byte filter_method;
    image_byte compression_type;
    image_byte interlace_type;
    image_type image_type;
    FILE *fp;
} image;


image *read_image(const char *filepath);

png_bytep *get_matrix_pointers_RGB(const image *image, png_uint_32 height);

void cleanup_image(image *image);


#endif //LIBIMAGEC_LIBIMAGEC_H
