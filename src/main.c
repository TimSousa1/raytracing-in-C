#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "3d.h"

#define WIDTH 100
#define HEIGHT 100
#define PIXEL_SIZE .1

#define CAM_DISTANCE 5
#define STEP .01
#define IT_LIMIT 1000

int main(int argc, char **argv){
    if (argc != 2) {
        fprintf(stdout, "Usage: ./render <out_filename>\n");
        return 1;
    }
    char *out_filename = argv[1];

    Image image;
    image.width = WIDTH;
    image.height = HEIGHT;

    image.pixel_array = calloc(image.width,  sizeof(Color *));
    for (int x = 0; x < image.width; x++){
        image.pixel_array[x] = calloc(image.height, sizeof(Color));
    }

    Camera mainCam;
    mainCam.position = (Vector3) {
        .x = (float) image.width*PIXEL_SIZE/2,
        .y = (float) image.height*PIXEL_SIZE/2,
        .z = CAM_DISTANCE
    };
    mainCam.screenDistance = -CAM_DISTANCE;

    mainCam.direction = (Vector3) {0, 0, -1};


    Ray cameraRay;
    cameraRay.origin = mainCam.position;

    Vector3 screenTopLeft = {
        .x = 0,
        .y = image.height*PIXEL_SIZE,
        .z = 0,
    };

    Cube test;
    test.size    = (Vector3) {1.0f, 1.0f,  1.0f};
    test.topleft = (Vector3) {image.width*PIXEL_SIZE/2 - test.size.x/2, image.height*PIXEL_SIZE/2 + test.size.y, -3 + test.size.z/2};

    Vector3 pixelPos;
    float step = 0.1;
    int x = 0, y = 0;
    for (int x = 0; x < image.width; x++){
        for (int y = 0; y < image.height; y++){
            pixelPos = addV3(screenTopLeft, (Vector3) {x*PIXEL_SIZE, - y * PIXEL_SIZE, 0});
            Vector3 camdir = subV3(pixelPos, cameraRay.origin);
            cameraRay.direction = normV3(camdir);
#ifdef DEBUG
            printV3(pixelPos);
            printf(" - ");
            printV3(cameraRay.origin);
            printf(" = ");
            printV3(camdir);
            printf("\n");
            printf("cameraRay.direction: "); printV3(cameraRay.direction); printf("\n");
#endif

            Vector3 z_search = cameraRay.origin;
            Vector3 step = scaleV3(cameraRay.direction, STEP);
            for (int z = 0; z < IT_LIMIT; z++){
                z_search = addV3(z_search, step);
                if (collCube(z_search, test)){
                    image.pixel_array[x][y] = (Color) {255, 0, 0};
                    break;
                }
            }
        }
    }

    render_image(image, out_filename);
    free_image(image);
    return 0;
}
