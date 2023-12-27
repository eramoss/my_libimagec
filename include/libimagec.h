#ifndef LIBIMAGEC_LIBIMAGEC_H
#define LIBIMAGEC_LIBIMAGEC_H

#include "stdio.h"
#include "stdlib.h"
#include "../lib/libpng-1.6.40/png.h"

png_image *create_png_structure();

unsigned read_png(png_image *png_handler, const char *filepath);

#endif //LIBIMAGEC_LIBIMAGEC_H
