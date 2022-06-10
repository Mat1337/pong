//
// Created by mat on 6/9/2022.
//

#ifndef PONG_CLONE_WINDOW_H
#define PONG_CLONE_WINDOW_H

#include <GLFW/glfw3.h>

#include "input/mouse.h"

typedef struct window_t {
    int width;
    int height;
    int has_focus;
} WINDOW;

// global handle for the window
extern WINDOW g_window;

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
 * Closes the window
 */

extern void window_close();

#endif //PONG_CLONE_WINDOW_H
