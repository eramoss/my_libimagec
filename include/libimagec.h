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
} png_infos;


png_infos *read_png_file(const char *filepath);

png_bytep *get_matrix_pointers_RGB(const png_infos *png, png_uint_32 height);

void optimize_dip_depth_color_type(const png_infos *png, png_byte color_type, png_byte bit_depth);

int recognize_png(const char *filename, FILE *fp);

void create_png_structp(FILE *fp, png_structp *png_ptr, png_infop *info_ptr);

void cleanup_png(png_infos *png);


#endif //LIBIMAGEC_LIBIMAGEC_H
