#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "3d.h"

#define WIDTH  500
#define HEIGHT 500
#define PIXEL_SIZE .1

#define CAM_DISTANCE 3
#define STEP .01
#define IT_LIMIT 1000

int main(int argc, char **argv){
    // add default filename 
    if (argc != 2) {
        fprintf(stdout, "Usage: ./render <out_filename>\n");
        return 1;
    }
    char *out_filename = argv[1];

    Image image;
    image.width = WIDTH;
    image.height = HEIGHT;

    image.pixel_array = calloc(image.width,  sizeof(Color *));
    for (int y = 0; y < image.height; y++){
        image.pixel_array[y] = calloc(image.width, sizeof(Color));
    }

    Camera mainCam;
    mainCam.position = (Vector3) {
        .x = (float) image.width*PIXEL_SIZE,
        .y = (float) image.height*PIXEL_SIZE/2,
        .z = 5
    };
    mainCam.screenDistance = 2;

    mainCam.direction = normV3((Vector3) {-1, 0, -1});
    mainCam.up        = normV3((Vector3) {0, 1, 0});

    Ray cameraRay;
    cameraRay.origin = mainCam.position;
    // expects normalized V3s
    M32 screenTransf = {
        .x = scaleV3(perpV3(mainCam.direction, mainCam.up), PIXEL_SIZE),
        .y = scaleV3(mainCam.up, PIXEL_SIZE)
    };

    M32 findTopLeft = {
        .x = scaleV3(screenTransf.x, -(float)image.width/2),
        .y = scaleV3(screenTransf.y, (float)image.height/2)
    };

    Vector3 screenCenter = addV3(mainCam.position, scaleV3(mainCam.direction, mainCam.screenDistance));
    Vector3 screenTopLeft = addV3(addV3(screenCenter, findTopLeft.x), findTopLeft.y);

#ifdef DEBUG
    printf("CameraPos: "); printV3(mainCam.position); printf("\n");
    printf("Screen Coord Transf: \n");
    printM32(screenTransf);
    printf("\n");

    printf("findTopLeft: \n");
    printM32(findTopLeft);
    printf("\n");

    printf("found screen center at: "); printV3(screenCenter); printf("\n");
    printf("found screen top left at: "); printV3(screenTopLeft); printf("\n");
#endif

    Cube test;
    test.size    = (Vector3) {1.0f, 1.0f,  1.0f};
    test.topleft = addV3(screenCenter, (Vector3){-test.size.x / 2, test.size.y/2, -test.size.z/2});

    test.color = (Color) {255, 0, 255};

    Vector3 pixelPos = screenTopLeft;
    for (int y = 0; y < image.height; y++){
        if (y != 0)
            pixelPos = scaleV3(screenTransf.y, y);
        for (int x = 0; x < image.width; x++){
            Vector3 camdir = subV3(pixelPos, cameraRay.origin);
            cameraRay.direction = normV3(camdir);
#ifdef DEBUG
            printf("pixelPos: "); printV3(pixelPos); printf("\n");
            printf("cameraRay.direction: "); printV3(cameraRay.direction); printf("\n");
#endif
            Vector3 z_search = cameraRay.origin;
            Vector3 step = scaleV3(cameraRay.direction, STEP);
            for (int z = 0; z < IT_LIMIT; z++){
                z_search = addV3(z_search, step);
                if (collCube(z_search, test)){
                    image.pixel_array[y][x] = test.color;
                    break;
                }
            }
            pixelPos = addV3(pixelPos, screenTransf.x);
        }
    }

    save_image(image, out_filename);
    free_image(image);
    return 0;
}
