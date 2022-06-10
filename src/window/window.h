//
// Created by mat on 6/9/2022.
//

#ifndef PONG_CLONE_WINDOW_H
#define PONG_CLONE_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "time_step.h"
#include "input/mouse.h"
#include "input/keyboard.h"

#include "../graphics/render.h"

typedef struct window_t {
    GLFWwindow *handle;
    int width;
    int height;
    int has_focus;
} WINDOW;

/**
 * Gets called when the window is resized
 *
 * @param window_handle handle of the window that was resized
 * @param width width that the window was resized to
 * @param height height that the window as resized to
 */

void on_window_resize(GLFWwindow *window_handle, int width, int height);

/**
 * Gets called when the focus state changes in the window
 *
 * @param window_handle handle of the window that was resized
 * @param focused 1 = gained focus, 0 = lost focus
 */

void on_window_focus_change(GLFWwindow *window_handle, int focused);

/**
 * Initializes the window
 */

void window_initialize();

/**
 * Runs the window loop
 */

void window_run();

/**
 * Frees any memory that the window might take
 */

void window_free();

/**
 * Closes the window
 */

void window_close();

/**
 * Gets called every render frame
 *
 * @param width width of the window
 * @param height height of the window
 * @param mouse_x x coordinate of the mouse in the window
 * @param mouse_y y coordinate of the mouse in the window
 * @param time_step time between two render ticks
 */

extern void on_render(float width, float height, float mouse_x, float mouse_y, float time_step);

/**
 * Gets called when the window closes
 */

extern void on_close();

#endif //PONG_CLONE_WINDOW_H
