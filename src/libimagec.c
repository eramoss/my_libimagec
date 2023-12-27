#include "libimagec.h"

void recognize_png(const char *filename, FILE *fp);

void create_png_structp(FILE *fp, png_structp *png_ptr, png_infop *info_ptr);

void error_handler(png_structp png_ptr, png_const_charp error_msg) {
    fprintf(stderr, "PNG Error: %s\n", error_msg);
    longjmp(png_jmpbuf(png_ptr), 1);
}

void warning_handler(png_structp png_ptr, png_const_charp warning_msg) {
    fprintf(stderr, "PNG Warning: %s\n", warning_msg);
}


void read_png_file(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening PNG file");
        exit(EXIT_FAILURE);
    }

    recognize_png(filename, fp);

    png_structp *png_ptr = malloc(sizeof(png_structp));
    png_infop *info_ptr = malloc(sizeof(png_infop));
    create_png_structp(fp, png_ptr, info_ptr);

    // Example: Get image width and height
    png_uint_32 width, height;
    int bit_depth, color_type;
    png_get_IHDR(*png_ptr, *info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

    printf("Image Width: %u\n", width);
    printf("Image Height: %u\n", height);

    // Cleanup
    png_destroy_read_struct(png_ptr, info_ptr, NULL);
    fclose(fp);
}

void create_png_structp(FILE *fp, png_structp *png_ptr, png_infop *info_ptr) {
    (*png_ptr) = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, error_handler, warning_handler);
    (*info_ptr) = png_create_info_struct(png_ptr);
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

void recognize_png(const char *filename, FILE *fp) {
    png_byte header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        fprintf(stderr, "File %s is not recognized as a PNG file\n", filename);
        fclose(fp);
        exit(EXIT_FAILURE);
    }
}

