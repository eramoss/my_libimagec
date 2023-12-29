#include <stdio.h>
#include <stdlib.h>
#include "libimagec.h"


FILE *get_file(const char *filename);

image *create_png_image(FILE *fp);

image *png_set_image_fields(png_structp *png_ptr, png_infop *info_ptr);

image *read_image(const char *filename) {
    FILE *fp = get_file(filename);

    if (recognize_png(filename, fp) == 0) {
        return create_png_image(fp);
    }
    exit(EXIT_FAILURE);
}

image *create_png_image(FILE *fp) {
    png_structp *png_ptr = malloc(sizeof(png_structp));
    png_infop *info_ptr = malloc(sizeof(png_infop));
    create_png_structp(fp, png_ptr, info_ptr);

    image *png_handler = png_set_image_fields(png_ptr, info_ptr);
    return png_handler;
}

void cleanup_image(image *image) {// Cleanup
    png_destroy_read_struct(image->png_ptr, image->info_ptr, NULL);
    free(image->fp);
    free(image);
}

FILE *get_file(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening PNG file");
        exit(EXIT_FAILURE);
    }
    return fp;
}

image *png_set_image_fields(png_structp *png_ptr, png_infop *info_ptr) {
    image *png_handler = malloc(sizeof(image));
    png_handler->info_ptr = info_ptr;
    png_handler->png_ptr = png_ptr;
    png_handler->width = png_get_image_width(*png_handler->png_ptr, *png_handler->info_ptr);
    png_handler->height = png_get_image_height(*png_handler->png_ptr, *png_handler->info_ptr);
    png_handler->bit_depth = png_get_bit_depth(*png_handler->png_ptr, *png_handler->info_ptr);
    png_handler->color_type = png_get_color_type(*png_handler->png_ptr, *png_handler->info_ptr);
    png_handler->channels = png_get_channels(*png_handler->png_ptr, *png_handler->info_ptr);
    png_handler->compression_type = png_get_compression_type(*png_handler->png_ptr, *png_handler->info_ptr);
    png_handler->filter_method = png_get_filter_type(*png_handler->png_ptr, *png_handler->info_ptr);
    png_handler->interlace_type = png_get_interlace_type(*png_handler->png_ptr, *png_handler->info_ptr);
    png_handler->image_type = PNG_IMAGE_TYPE;
    return png_handler;
}


