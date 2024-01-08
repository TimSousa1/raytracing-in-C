#ifndef T_RENDER
#define T_RENDER

#include <stdio.h>
#include <stdlib.h>

#define BIT_DEPTH 255

typedef struct {
    float x;
    float  y;
} Vector2;


typedef struct {
    int r;
    int g;
    int b;
} Color;

typedef struct {
    Color **pixel_array;

    int width;
    int height;
} Image;

int render_image(Image, char *out_filename);
void free_image(Image image);

int convert(float conv, Vector2 init, Vector2 final);
#endif
