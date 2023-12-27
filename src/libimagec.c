#include "libimagec.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

unsigned read_png(png_image *png_holder, const char *filepath) {
    if (png_holder == NULL) return 1;
    if (png_image_begin_read_from_file(png_holder, filepath) != 0) {
        png_bytep buffer;

        png_holder->format = PNG_FORMAT_RGBA;

        buffer = malloc(PNG_IMAGE_SIZE(*png_holder));

        if (buffer != NULL &&
            png_image_finish_read(png_holder, NULL/*background*/, buffer,
                                  0/*row_stride*/, NULL/*colormap*/) != 0)
            return 0;
    }

    /* Something went wrong reading.  libpng stores a
     * textual message in the 'png_image' structure:
     */
    fprintf(stderr, "pngtopng: error: %s\n", png_holder->message);
    return 2;

}

png_image *create_png_structure() {
    png_image *image = malloc(sizeof(png_image)); // control structure of libpng
    /* initialize default values */
    image->version = PNG_IMAGE_VERSION;

    return image;
}