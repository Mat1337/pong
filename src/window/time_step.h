//
// Created by mat on 6/10/2022.
//

#ifndef PONG_CLONE_TIME_STEP_H
#define PONG_CLONE_TIME_STEP_H

#include <GLFW/glfw3.h>

/**
 * Updates the time step
 */

void time_step_update();

/**
 * Gets the time step
 *
 * @return time step in between two render ticks in seconds
 */

float time_step_get();

#endif //PONG_CLONE_TIME_STEP_H
