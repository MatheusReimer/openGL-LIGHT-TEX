#ifndef AXIS_H
#define AXIS_H

#include <math.h>

struct Axis {
    bool x;
    bool y;
    bool z;
};

float calculateFirstLineOfRotationMatrix(float a, float b, float angleInRadians);
float calculateSecondLineOfRotationMatrix(float a, float b, float angleInRadians);

#endif // AXIS_H
