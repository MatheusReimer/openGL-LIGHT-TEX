#include "vector3.h"

Vector3 addVector3(Vector3 a, Vector3 b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 subtractVector3(Vector3 a, Vector3 b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Vector3 scaleVector3(Vector3 a, Scale scale) {
    return {a.x * scale.x, a.y * scale.y, a.z * scale.z};
}

Vector3 rotateVector3(Vector3 a, float angle, Axis axis) {
    float radians = angle * (3.14f / 180.0f);
    float x = a.x, y = a.y, z = a.z;

    if (axis.x) {
        float temp = calculateFirstLineOfRotationMatrix(y, z, radians);
        z = calculateSecondLineOfRotationMatrix(y, z, radians);
        y = temp;
    } else if (axis.y) {
        float temp = calculateFirstLineOfRotationMatrix(z, x, radians);
        x = calculateSecondLineOfRotationMatrix(z, x, radians);
        z = temp;
    } else if (axis.z) {
        float temp = calculateFirstLineOfRotationMatrix(x, y, radians);
        y = calculateSecondLineOfRotationMatrix(x, y, radians);
        x = temp;
    }

    return {x, y, z};
}
