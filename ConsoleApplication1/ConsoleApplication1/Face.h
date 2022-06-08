#ifndef FACE_H
#define FACE_H

#include "vector2.h"
#include "vector3.h"

#include <vector>
#include <stdlib.h>

using namespace std;

class Face {
public:
    std::vector<int> vertices;
    std::vector<int> uvs;
    std::vector<int> normals;

    float rColor, gColor, bColor;

    Face() {
        rColor = (rand() % 501) / 1000.0;
        gColor = (rand() % 501) / 1000.0;
        bColor = (rand() % 501) / 1000.0;
    }
};


#endif // FACE_H
