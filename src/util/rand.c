//
// Created by mat on 6/12/2022.
//

#include "rand.h"

/**
 * Generates a floating pointer number
 * between two provided values
 *
 * @param min minimum value that can generate
 * @param max  maximum value that can generate
 * @return random number between min & max
 */

float rand_float(float min, float max) {
    return (((float) rand() / (float) RAND_MAX) * (max - min)) + min;
}