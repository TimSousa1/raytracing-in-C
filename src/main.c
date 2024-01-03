#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define WIDTH 100
#define HEIGHT 100

int main(int argc, char **argv){
    if (argc != 2) {
        fprintf(stdout, "Usage: ./render <out_filename>\n");
        return 1;
    }
    char *out_filename = argv[1];

    Image image;
    image.pixel_array = calloc(WIDTH,  sizeof(Color *));
    for (int x = 0; x < WIDTH; x++){
        image.pixel_array[x] = calloc(HEIGHT, sizeof(Color));
    }
    image.width = WIDTH;
    image.height = HEIGHT;

    // writing something on the array (test)
    for (int x = 0; x < image.width; x++){
        for (int y = 0; y < image.height; y++){
            float converted_x = convert(x, (Vector2) {0, WIDTH}, (Vector2) {0, BIT_DEPTH});
            float converted_y = convert(y, (Vector2) {0, HEIGHT}, (Vector2) {0, BIT_DEPTH});

            image.pixel_array[x][y] = (Color) {converted_x, converted_y, 0};
        }
    }

    render_image(image, out_filename);
    free_image(image);
    return 0;
}
