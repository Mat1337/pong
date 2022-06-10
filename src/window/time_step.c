//
// Created by mat on 6/10/2022.
//

#include "time_step.h"

float delta = 0.0f;
float last_time = 0.0f;
float current_fps = 0.0f;
float avg_fps;
float counter = 0;

/**
 * Updates the time step
 */

void time_step_update() {
    // get the time from the glfw
    float time = (float) glfwGetTime();

    // calculate the delta in seconds
    delta = time - last_time;

    // add the current fps
    current_fps += 1.0f / delta;

    // if the avg fps is not set
    if (!avg_fps) {
        // set the avg fps to current fps
        avg_fps = current_fps;
    } else if (counter >= 75) {
        // calculate the avg fps
        avg_fps = current_fps / (float) counter;

        // reset the current fps & the counter back to 0
        current_fps = 0;
        counter = 0;
    }

    // increment the counter
    counter++;

    // update the last time
    last_time = time;
}

/**
 * Gets the current fps
 *
 * @return frames per second
 */

float time_fps_get() {
    return avg_fps;
}

/**
 * Gets the time step
 *
 * @return time step in between two render ticks in seconds
 */

float time_step_get() {
    return delta;
}