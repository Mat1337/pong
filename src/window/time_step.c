//
// Created by mat on 6/10/2022.
//

#include "time_step.h"

float delta = 0.0f;
float last_time = 0.0f;

/**
 * Updates the time step
 */

void time_step_update() {
    // get the time from the glfw
    float time = (float) glfwGetTime();

    // calculate the delta in seconds
    delta = time - last_time;

    // update the last time
    last_time = time;
}

/**
 * Gets the time step
 *
 * @return time step in between two render ticks in seconds
 */

float time_step_get() {
    return delta;
}