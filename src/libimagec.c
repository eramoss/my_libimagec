#include "libimagec.h"


void error_handler(png_structp png_ptr, png_const_charp error_msg) {
    fprintf(stderr, "PNG Error: %s\n", error_msg);
    longjmp(png_jmpbuf(png_ptr), 1);
}

void warning_handler(png_structp png_ptr, png_const_charp warning_msg) {
    fprintf(stderr, "PNG Warning: %s\n", warning_msg);
}


png_infos *read_png_file(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening PNG file");
        exit(EXIT_FAILURE);
    }

    recognize_png(filename, fp);

    png_structp *png_ptr = malloc(sizeof(png_structp));
    png_infop *info_ptr = malloc(sizeof(png_infop));
    create_png_structp(fp, png_ptr, info_ptr);

    png_infos *png_handler = malloc(sizeof(png_infos));
    png_handler->info_ptr = info_ptr;
    png_handler->png_ptr = png_ptr;
    png_handler->fp = fp;
    return png_handler;
}

void cleanup_png(png_infos *png) {// Cleanup
    png_destroy_read_struct(png->png_ptr, png->info_ptr, NULL);
    fclose(png->fp);
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

int recognize_png(const char *filename, FILE *fp) {
    png_byte header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        fprintf(stderr, "File %s is not recognized as a PNG file\n", filename);
        fclose(fp);
        return 1;
    }
    return 0;
}

