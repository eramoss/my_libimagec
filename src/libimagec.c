#include <stdio.h>
#include "libimagec.h"

Image *load_image(const char *file_path) {

    return NULL;
}

void save_image(const char *file_path, const Image *image) {

}

void free_image(Image *image) {

}

Image *resize_image(const Image *image, int new_width, int new_height) {

    return NULL; // Placeholder, actual implementation needed
}

ImageFormat image_format(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        fprintf(stderr, "Error opening file: nonexistent_file.txt\n");
        // Unable to open the file
        return UNKNOWN;
    }

    png_byte header[8];
    fread(header, 1, sizeof(header), file);

    // Check if the file is a PNG by using libpng functions
    if (png_sig_cmp(header, 0, 8) == 0) {
        fclose(file);
        return PNG;
    }
    // Add more checks for other formats as needed

    fclose(file);
    return UNKNOWN;
}