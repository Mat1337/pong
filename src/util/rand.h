//
// Created by mat on 6/12/2022.
//

#ifndef PONG_CLONE_RAND_H
#define PONG_CLONE_RAND_H

#include <time.h>
#include <stdlib.h>

/**
 * Generates a floating pointer number
 * between two provided values
 *
 * @param min minimum value that can generate
 * @param max  maximum value that can generate
 * @return random number between min & max
 */

float rand_float(float min, float max);

#endif //PONG_CLONE_RAND_H
