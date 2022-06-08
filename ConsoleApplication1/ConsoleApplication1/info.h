#ifndef MESH_H
#define MESH_H

#include "vector3.h"
#include "vector2.h"
#include "scale.h"
#include "rotation.h"
#include "face.h"

#include <vector>

class Mesh {
public:
    Vector3 position = {0, 0, 0};
    Rotation rotation = {0, 0, 0};
    Scale scale = {1, 1, 1};

    std::vector<Vector3> vertices;
    std::vector<Vector2> uvs;
    std::vector<Vector3> normals;
    std::vector<Face> faces;

    Mesh();
    void translateBy(Vector3 translation);
    void scaleBy(Scale scale);
    void rotateBy(float angle, Axis axis);
};

#endif // MESH_H
