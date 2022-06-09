//
// Created by mat on 6/9/2022.
//

#include "graphics/font.h"
#include "graphics/render.h"
#include "graphics/shader.h"

typedef struct window_t {
    int width;
    int height;
    int has_focus;
} WINDOW;
WINDOW window;

/**
 * Gets called when the window is resized
 *
 * @param window_handle handle of the window that was resized
 * @param width width that the window was resized to
 * @param height height that the window as resized to
 */

void on_window_resize(GLFWwindow *window_handle, int width, int height) {
    window.width = width;
    window.height = height;
}

/**
 * Gets called when the focus state changes in the window
 *
 * @param window_handle handle of the window that was resized
 * @param focused 1 = gained focus, 0 = lost focus
 */

void on_window_focus_change(GLFWwindow *window_handle, int focused) {
    window.has_focus = focused;
}

int main(void) {
    // define a new window handle
    GLFWwindow *window_handle;

    // setup the window settings
    window.width = 640;
    window.height = 480;
    window.has_focus = 1;

    // initialize the library
    if (!glfwInit())
        return -1;

    // disable window resizing
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // create a windowed mode window and its opengl context
    window_handle = glfwCreateWindow(window.width, window.height, "Pong", NULL, NULL);
    if (!window_handle) {
        glfwTerminate();
        return -1;
    }

    // make current context
    glfwMakeContextCurrent(window_handle);

    // initialize the glew
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("ERR: %s\n", glewGetErrorString(err));
        exit(1);
    }

    // setup the window callbacks
    glfwSetWindowSizeCallback(window_handle, &on_window_resize);
    glfwSetWindowFocusCallback(window_handle, &on_window_focus_change);

    // make the window's context current
    glfwMakeContextCurrent(window_handle);

    // initialize the font from memory
    if (font_initialize("res/bit_font.ttf", 17) != 0) {
        // terminate the glfw
        glfwTerminate();

        // return out of the application
        return 1;
    }

    // load all the shaders into the memory
    shader_load_shaders();

    // loop until the user closes the window
    while (!glfwWindowShouldClose(window_handle)) {
        // clear the screen color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // setup the 2D rendering
        render_setup_overlay(window.width, window.height);

        // push new matrix
        glPushMatrix();

        // render text to screen
        render_text(window.has_focus == 1 ? "Hello, World!" : "Paused", 5, 5, 2.0f);

        // pop matrix
        glPopMatrix();

        /* Swap front and back buffers */
        glfwSwapBuffers(window_handle);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // free the window callbacks
    glfwSetWindowSizeCallback(window_handle, NULL);
    glfwSetWindowFocusCallback(window_handle, NULL);

    // free font from memory
    font_free();

    // terminate the glfw
    glfwTerminate();

    // return out of the application
    return 0;
}