typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    Vector3 topleft;
    Vector3 size;
} Cube;

typedef struct {
    Vector3 position;
    Vector3 direction;
    float   screenDistance; // distance to the virtual screen (higher distance -- higer FOV)
} Camera;

typedef struct {
    Vector3 origin;
    Vector3 direction;
} Ray;

// Vector Math
Vector3 addV3   (Vector3 v1, Vector3 v2);
Vector3 subV3   (Vector3 v1, Vector3 v2);
Vector3 scaleV3 (Vector3 v, float scalar);
float   modsqV3 (Vector3 v);
Vector3 normV3  (Vector3 v);
void    printV3 (Vector3 v);

int  collCube  (Vector3 v, Cube c);
void printCube (Cube c);
