#ifndef VECTOR3_H
#define VECTOR3_H

#include "scale.h"
#include "axis.h"

struct Vector3 {
    float x;
    float y;
    float z;
};

Vector3 addVector3(Vector3 a, Vector3 b);
Vector3 subtractVector3(Vector3 a, Vector3 b);
Vector3 scaleVector3(Vector3 a, Scale scale);
Vector3 rotateVector3(Vector3 a, float angle, Axis axis);

#endif // VECTOR3_H
