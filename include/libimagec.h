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
    png_infop info_p;
    png_structp struct_p;
} LibPngBaseStructure;

typedef struct {
    int width;
    int height;
    unsigned char *data; // Assuming images are represented as raw pixel data
    ImageFormat format;
    LibPngBaseStructure *png_p;
} Image;


Image *load_image(const char *file_path);

void save_image(const char *file_path, const Image *image);

void free_image(Image *image);

ImageFormat image_format(const char *file_path);

#endif //LIBIMAGEC_LIBIMAGEC_H
