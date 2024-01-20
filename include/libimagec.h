#ifndef LIBIMAGEC_LIBIMAGEC_H
#define LIBIMAGEC_LIBIMAGEC_H

#include "png_interface.h"

// Enum to represent different image formats
typedef enum {
    PNG,
    JPEG,
    BMP,
} ImageFormat;

// Structure to represent an image
typedef struct {
    int width;
    int height;
    unsigned char *data; // Assuming image data is represented as a byte array
    ImageFormat format;
} Image;

// Function to load an image from a file
Image loadImage(const char *filePath);

// Function to save an image to a file
bool saveImage(const char *filePath, const Image *image, ImageFormat format);

// Function to free memory allocated for an image
void freeImage(Image *image);


#endif //LIBIMAGEC_LIBIMAGEC_H
