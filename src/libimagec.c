#include "libimagec.h"

unsigned load_raw_file(raw_png_t *png_handler, const char *filename) {
    unsigned char **out = &(png_handler->vector_png);
    size_t *outsize = &(png_handler->vector_png_size);
    FILE *file;
    long size;

    /*provide some proper output values if error will happen*/
    *out = 0;
    *outsize = 0;

    file = fopen(filename, "rb");
    if (!file) return 78;

    /*get filesize:*/
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    /*read contents of the file into the vector*/
    *outsize = 0;
    *out = (unsigned char *) malloc((size_t) size);
    if (size && (*out)) (*outsize) = fread(*out, 1, (size_t) size, file);

    fclose(file);
    if (!(*out) && size) return 83; /*the above malloc failed*/
    return 0;
}

unsigned decompress_png_huffman(raw_png_t *png_handler) {}
