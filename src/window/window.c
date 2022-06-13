//
// Created by mat on 6/9/2022.
//

#include "window.h"

// define the base bounds of the window
static const int WIDTH = 640;
static const int HEIGHT = 480;

// used for accessing window information
WINDOW g_window;

/**
 * Gets called when the window is resized
 *
 * @param window_handle handle of the window that was resized
 * @param width width that the window was resized to
 * @param height height that the window as resized to
 */

void on_window_resize(GLFWwindow *window_handle, int width, int height) {
    g_window.width = width;
    g_window.height = height;
}

/**
 * Gets called when the focus state changes in the window
 *
 * @param window_handle handle of the window that was resized
 * @param focused 1 = gained focus, 0 = lost focus
 */

void on_window_focus_change(GLFWwindow *window_handle, int focused) {
    g_window.has_focus = focused;
}

/**
 * Initializes the window
 */

void window_initialize() {
    // setup the window settings
    g_window.width = WIDTH;
    g_window.height = HEIGHT;
    g_window.has_focus = 1;

    // initialize the library
    if (!glfwInit()) {
        return;
    }

    // disable window resizing
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // create a windowed mode window and its opengl context
    g_window.handle = glfwCreateWindow(g_window.width, g_window.height, "Pong", NULL, NULL);
    if (!g_window.handle) {
        // close the window
        window_close();
        return;
    }

    // make current context
    glfwMakeContextCurrent(g_window.handle);

    // initialize the glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        // close the window
        window_close();

        // return out of the method
        return;
    }

    // setup the window callbacks
    glfwSetWindowSizeCallback(g_window.handle, &on_window_resize);
    glfwSetWindowFocusCallback(g_window.handle, &on_window_focus_change);

    // setup the input callbacks
    glfwSetMouseButtonCallback(g_window.handle, &on_mouse_input);
    glfwSetCursorPosCallback(g_window.handle, &on_mouse_move);
    glfwSetKeyCallback(g_window.handle, &on_key_input);
}

/**
 * Runs the window loop
 */

void window_run() {
    // loop until the user closes the window
    while (!glfwWindowShouldClose(g_window.handle)) {
        // update the time step
        time_step_update();

        // clear the screen color buffer
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // setup the 2D rendering
        render_setup_overlay(g_window.width, g_window.height);

        // call the render function
        on_render((float) g_window.width, (float) g_window.height,
                  g_mouse.x, g_mouse.y, time_step_get());

        // swap front and back buffers
        glfwSwapBuffers(g_window.handle);

        // reset the mouse
        mouse_reset();

        // poll for and process events
        glfwPollEvents();
    }
}

/**
 * Returns the width of the window
 *
 * @return width of the window
 */

int window_get_width() {
    return g_window.width;
}

/**
 * Returns the height of the window
 *
 * @return height of the window
 */

int window_get_height() {
    return g_window.height;
}

/**
 * Checks if the window has focus
 *
 * @return returns flag that says if the window has focus or not
 */

int window_has_focus() {
    return g_window.has_focus;
}

/**
 * Frees any memory that the window might take
 */

void window_free() {
    // free the window callbacks
    glfwSetWindowSizeCallback(g_window.handle, NULL);
    glfwSetWindowFocusCallback(g_window.handle, NULL);

    // free the input callbacks
    glfwSetMouseButtonCallback(g_window.handle, NULL);
    glfwSetCursorPosCallback(g_window.handle, NULL);
    glfwSetKeyCallback(g_window.handle, NULL);
}


/**
 * Closes the window
 */

void window_close() {
    // queue the window for closing
    glfwSetWindowShouldClose(g_window.handle, GL_TRUE);
}