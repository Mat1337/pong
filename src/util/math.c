//
// Created by mat on 6/12/2022.
//

#include "math.h"

float math_rad(float ang) {
    return M_PI * ang / 180.0f;
}

float math_map_float(float value, float from, float to, float min, float max) {
    return (value - from) * (max - min) / (to - from) + min;
}