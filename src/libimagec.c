#include <stdio.h>
#include "libimagec.h"
#include "../utils/files.h"
#include <stdlib.h>
#include <string.h>

Image *create_png_image(FILE *fp);

void save_png(const Image *image, FILE *fp);

Image *load_image(const char *file_path) {
    FILE *fp = fopen_read_bytes(file_path);
    if (image_format(file_path) == PNG) return create_png_image(fp);

    return NULL;
}

void save_image(const char *file_path, const Image *image) {
    if (!file_path || !image) {
        fprintf(stderr, "Invalid arguments for save_image\n");
        return;
    }

    FILE *fp = fopen_write_bytes(file_path);

    if (image->format == PNG) save_png(image, fp);

}

void save_png(const Image *image, FILE *fp) {
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png) {
        fprintf(stderr, "Error creating PNG write structure\n");
        fclose(fp);
        return;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        fprintf(stderr, "Error creating PNG info structure\n");
        png_destroy_write_struct(&png, NULL);
        fclose(fp);
        return;
    }

    if (setjmp(png_jmpbuf(png))) {
        fprintf(stderr, "Error during PNG creation\n");
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return;
    }

    png_init_io(png, fp);
    png_byte bit_depth = png_get_bit_depth(image->png_p->struct_p, image->png_p->info_p);
    png_byte color_type = png_get_color_type(image->png_p->struct_p, image->png_p->info_p);
    // Set image information
    png_set_IHDR(png, info, image->width, image->height, bit_depth,
                 color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    // Write image data
    png_bytep row_pointers[image->height];
    int bytes_per_pixel = (bit_depth / 8) * (color_type == PNG_COLOR_TYPE_RGBA ? 4 : 3);
    for (int i = 0; i < image->height; i++) {
        row_pointers[i] = image->data + i * image->width * bytes_per_pixel;
    }

    png_set_rows(png, info, row_pointers);
    png_write_png(png, info, PNG_TRANSFORM_IDENTITY, NULL);

    // Clean up
    png_destroy_write_struct(&png, &info);
    fclose(fp);
}

Image *create_png_image(FILE *fp) {
    png_structp png_p = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_p) {
        fprintf(stderr, "Error: Couldn't initialize PNG read structure\n");
        fclose(fp);
        return NULL;
    }

    png_infop info_p = png_create_info_struct(png_p);
    if (!info_p) {
        fprintf(stderr, "Error: Couldn't initialize PNG info structure\n");
        png_destroy_read_struct(&png_p, NULL, NULL);
        fclose(fp);
        return NULL;
    }


    png_init_io(png_p, fp);
    png_read_info(png_p, info_p);

    int width = (int) png_get_image_width(png_p, info_p);
    int height = (int) png_get_image_height(png_p, info_p);
    png_byte color_type = png_get_color_type(png_p, info_p);
    png_byte bit_depth = png_get_bit_depth(png_p, info_p);

    if (bit_depth == 16)
        png_set_strip_16(png_p);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_p);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_p);

    if (png_get_valid(png_p, info_p, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_p);

    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png_p, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_p);

    png_read_update_info(png_p, info_p);

    png_bytep *row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++)
        row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(png_p, info_p));

    png_read_image(png_p, row_pointers);

    fclose(fp);

    Image *image = (Image *) malloc(sizeof(Image));
    image->width = width;
    image->height = height;
    image->data = (unsigned char *) malloc(width * height * 4); // Assuming 4 channels (RGBA)

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            png_byte *ptr = &(row_pointers[y][x * 4]);
            image->data[(y * width + x) * 4 + 0] = ptr[0]; // Red channel
            image->data[(y * width + x) * 4 + 1] = ptr[1]; // Green channel
            image->data[(y * width + x) * 4 + 2] = ptr[2]; // Blue channel
            image->data[(y * width + x) * 4 + 3] = ptr[3]; // Alpha channel
        }
    }

    image->png_p = (LibPngBaseStructure *) malloc(sizeof(LibPngBaseStructure));
    image->png_p->info_p = info_p;
    image->png_p->struct_p = png_p;
    image->format = PNG;
    for (int y = 0; y < height; y++)
        free(row_pointers[y]);
    free(row_pointers);

    return image;
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