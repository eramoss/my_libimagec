#ifndef LIBIMAGEC_LIBIMAGEC_H
#define LIBIMAGEC_LIBIMAGEC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <zlib.h>
#include "../lib/libpng-1.6.40/png.h"

typedef struct {
    png_structp *png_ptr;
    png_infop *info_ptr;
    png_uint_16 width;
    png_uint_16 height;
    png_byte bit_depth;
    png_byte color_type;
    png_byte channels;
    png_byte filter_method;
    png_byte compression_type;
    png_byte interlace_type;
} image;


image *read_png_file(const char *filepath);

png_bytep *get_matrix_pointers_RGB(const image *png, png_uint_32 height);

void optimize_dip_depth_color_type(const image *png, png_byte color_type, png_byte bit_depth);

int recognize_png(const char *filename, FILE *fp);

void create_png_structp(FILE *fp, png_structp *png_ptr, png_infop *info_ptr);

void cleanup_png(image *png);


#endif //LIBIMAGEC_LIBIMAGEC_H
