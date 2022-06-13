//
// Created by mat on 6/12/2022.
//

#include "math.h"

/**
 * Converts angle to radians
 *
 * @param ang angle that you want to convert
 * @return angle in radians
 */

float math_rad(float ang) {
    return M_PI * ang / 180.0f;
}

/**
 * Maps a value to a range
 *
 * @param value value that you want to map
 * @param from minimum of the value
 * @param to maximum of the value
 * @param min min of the range
 * @param max max of the range
 * @return value from min to max based on the value
 */

float math_map_float(float value, float from, float to, float min, float max) {
    return (value - from) * (max - min) / (to - from) + min;
}