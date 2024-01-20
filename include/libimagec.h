#ifndef LIBIMAGEC_LIBIMAGEC_H
#define LIBIMAGEC_LIBIMAGEC_H

#include "libpng-1.6.40/png.h"

typedef enum {
    PNG,
    BMP,
    JPG,
    // ...
    UNKNOWN,
} ImageFormat;

typedef struct {
    int width;
    int height;
    unsigned char *data; // Assuming images are represented as raw pixel data
} Image;

Image *load_image(const char *file_path);

void save_image(const char *file_path, const Image *image);

void free_image(Image *image);

Image *resize_image(const Image *image, int new_width, int new_height);

ImageFormat image_format(const char *file_path);

#endif //LIBIMAGEC_LIBIMAGEC_H
