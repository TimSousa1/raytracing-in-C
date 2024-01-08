#include "3d.h"

#include <stdio.h>
# include <stdint.h> // uint32_t

// original quake III inverse square root (voiding UB with union)
// obsolete?
float q_rsqrt(float number)
{
  union {
    float    f;
    uint32_t i;
  } conv = { .f = number };
  conv.i  = 0x5f3759df - (conv.i >> 1);
  conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
  return conv.f;
}

int collCube(Vector3 v, Cube c) {
    if (v.x > c.topleft.x && v.x < c.topleft.x + c.size.x) {
        if (v.y < c.topleft.y && v.y > c.topleft.y - c.size.y) {
            if (v.z > c.topleft.z && v.z < c.topleft.z + c.size.z) {
                return 1;
            }
        }
    }
    return 0;
}

void printCube(Cube c) {
    printf("topleft: (%f, %f, %f)\n", c.topleft.x, c.topleft.y, c.topleft.z);
    printf("size: (%f, %f, %f)\n", c.size.x, c.size.y, c.size.z);
}

Vector3 addV3(Vector3 v1, Vector3 v2) {
    return (Vector3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vector3 subV3(Vector3 v1, Vector3 v2) {
    return (Vector3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vector3 scaleV3(Vector3 v, float scalar) {
    return (Vector3){v.x * scalar, v.y * scalar, v.z * scalar};
}

// mod of a vector (squared)
float modsqV3(Vector3 v) { 
    return v.x*v.x + v.y*v.y + v.z*v.z; 
}

Vector3 normV3(Vector3 v) {
    return scaleV3(v, q_rsqrt( modsqV3(v) ));
}

void printV3(Vector3 v) {
    printf("(%f, %f, %f)", v.x, v.y, v.z);
}
