//
// Created by mat on 6/9/2022.
//

#ifndef PONG_CLONE_WINDOW_H
#define PONG_CLONE_WINDOW_H

#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "time_step.h"
#include "input/mouse.h"
#include "input/keyboard.h"

#include "../graphics/render.h"

typedef struct window_t {
    GLFWwindow *handle;

    // used for post-processing
    FRAMEBUFFER *framebuffer;
    FRAMEBUFFER *framebuffer_effect;
    TEXTURE overlay_texture;
    int crt_resolution_id;

    float frame_buffer_x;
    float frame_buffer_y;
    float frame_buffer_width;
    float frame_buffer_height;

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
 * Gets called when the mouse is pressed
 *
 * @param button button that was pressed
 * @param x x coordinate of the mouse on the window
 * @param y y coordinate of the mouse on the window
 */


void on_window_mouse_press(int button, float x, float y);

/**
 * Gets called when the mouse is released
 *
 * @param button button that was pressed
 * @param x x coordinate of the mouse on the window
 * @param y y coordinate of the mouse on the window
 */


void on_window_mouse_release(int button, float x, float y);

/**
 * Initializes the window
 */

void window_initialize();

/**
 * Runs the window loop
 */

void window_run();

/**
 * Returns the width of the window
 *
 * @return width of the window
 */

int window_get_width();

/**
 * Returns the height of the window
 *
 * @return height of the window
 */

int window_get_height();

/**
 * Gets the start x location of the framebuffer
 *
 * @return x coordinate of the framebuffer
 */

float window_framebuffer_x();

/**
 * Gets the start y location of the framebuffer
 *
 * @return y coordinate of the framebuffer
 */

float window_framebuffer_y();

/**
 * Gets the width of the framebuffer
 *
 * @return width of the framebuffer
 */

float window_framebuffer_width();

/**
 * Gets the height of the framebuffer
 *
 * @return height of the framebuffer
 */

float window_framebuffer_height();

/**
 * Checks if the window has focus
 *
 * @return returns flag that says if the window has focus or not
 */

int window_has_focus();

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
