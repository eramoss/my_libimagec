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
    FILE *fp;
} png_infos;

png_infos *read_png_file(const char *filepath);

void recognize_png(const char *filename, FILE *fp);

void create_png_structp(FILE *fp, png_structp *png_ptr, png_infop *info_ptr);

void cleanup_png(png_infos *png);


#endif //LIBIMAGEC_LIBIMAGEC_H
