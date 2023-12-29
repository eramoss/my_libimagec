//
// Created by eramoss on 29/12/23.
//
#include "../include/png_interface.h"


void error_handler(png_structp png_ptr, png_const_charp error_msg) {
    fprintf(stderr, "PNG Error: %s\n", error_msg);
    longjmp(png_jmpbuf(png_ptr), 1);
}

void warning_handler(png_structp png_ptr, png_const_charp warning_msg) {
    fprintf(stderr, "PNG Warning: %s\n", warning_msg);
}

void create_png_structp(FILE *fp, png_structp *png_ptr, png_infop *info_ptr) {
    (*png_ptr) = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, error_handler, warning_handler);
    (*info_ptr) = png_create_info_struct((const png_struct *) png_ptr);
    if (!(*png_ptr)) {
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    if (!(*info_ptr)) {
        png_destroy_read_struct(png_ptr, NULL, NULL);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    if (setjmp(png_jmpbuf((*png_ptr)))) {
        png_destroy_read_struct(png_ptr, info_ptr, NULL);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    png_set_sig_bytes((*png_ptr), 8);
    png_init_io((*png_ptr), fp);
    png_read_info((*png_ptr), (*info_ptr));
}

void default_png_rgb_to_gray(png_structp *png_ptr, int error_code) {
    png_set_rgb_to_gray_fixed(
            *png_ptr, error_code, -1, -1
    );
}

unsigned recognize_png(const char *filename, FILE *fp) {
    png_byte header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        fprintf(stderr, "File %s is not recognized as a PNG file\n", filename);
        fclose(fp);
        return 1;
    }
    return 0;
}

png_bytep *get_matrix_pointers_RGB(png_structp *png_ptr, png_infop *info_ptr, png_uint_16 height) {
    png_bytep *row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++)
        row_pointers[y] = (png_byte *) malloc(png_get_rowbytes(*png_ptr, *info_ptr));

    png_read_image(*png_ptr, row_pointers);
    return row_pointers;
}
