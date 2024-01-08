#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int render_image(Image image, char *out_file){
    FILE *rendered_image = fopen(out_file, "w");
    if (!rendered_image) {
        fprintf(stderr, "Couldn't open file for saving!\n");
        return 1;
    }

    fprintf(rendered_image, "P3 %i %i %i\n", image.width, image.height, BIT_DEPTH);

    for (int x = 0; x < image.width; x++){
        for (int y = 0; y < image.height; y++){
            fprintf(rendered_image, "%i %i %i ", image.pixel_array[x][y].r,
                                                 image.pixel_array[x][y].g,
                                                 image.pixel_array[x][y].b);
        } 
        fprintf(rendered_image, "\n");
    }
    return 0;
}

// convert between two ranges
int convert(float conv, Vector2 init, Vector2 final){
    float idelta, fdelta, ret;
    idelta = init.y - init.x;
    fdelta = final.y - final.x;
    ret = (((conv - init.x) * fdelta) / idelta) + final.x;
    return ret;
}

void free_image(Image image){
    for (int x = 0; x < image.width; x++){
        free(image.pixel_array[x]);
    }
    free(image.pixel_array);
}
