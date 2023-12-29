#ifndef LIBIMAGEC_LIBIMAGEC_H
#define LIBIMAGEC_LIBIMAGEC_H

#include "png_interface.h"

typedef unsigned char image_byte;
typedef unsigned short image_uint_16;
typedef image_uint_16 image_type;

#define PNG_IMAGE_TYPE 0

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

void cleanup_image(image *image);


#endif //LIBIMAGEC_LIBIMAGEC_H
