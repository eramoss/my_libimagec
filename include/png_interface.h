//
// Created by eramoss on 29/12/23.
//

#ifndef LIBIMAGEC_PNG_INTERFACE_H
#define LIBIMAGEC_PNG_INTERFACE_H

#include "../lib/libpng-1.6.40/png.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <zlib.h>

void create_png_structp(FILE *fp, png_structp *png_ptr, png_infop *info_ptr);

unsigned recognize_png(const char *filename, FILE *fp);

png_bytep *get_matrix_pointers_RGB(png_structp *png_ptr, png_infop *info_ptr, png_uint_16 height);

#endif //LIBIMAGEC_PNG_INTERFACE_H
