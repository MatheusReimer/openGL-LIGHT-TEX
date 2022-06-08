#include "axis.h"

float calculateFirstLineOfRotationMatrix(float a, float b, float angleInRadians) {
    return a * cosf(angleInRadians) - b * sinf(angleInRadians);
}

float calculateSecondLineOfRotationMatrix(float a, float b, float angleInRadians) {
    return a * sinf(angleInRadians) + b * cosf(angleInRadians);
}
