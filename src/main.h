#ifndef T_RENDER
#define T_RENDER

#include <stdio.h>
#include <stdlib.h>

#define BIT_DEPTH 255

typedef struct {
    float x;
    float  y;
} Vector2;

#ifndef T_COLOR
#define T_COLOR

typedef struct {
    int r;
    int g;
    int b;
} Color;

#endif

typedef struct {
    Color **pixel_array;

    int width;
    int height;
} Image;

int save_image(Image, char *out_filename);
void free_image(Image image);

int convert(float conv, Vector2 init, Vector2 final);
#endif
