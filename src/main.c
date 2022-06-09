//
// Created by mat on 6/9/2022.
//

#include "graphics/render.h"
#include "window/window.h"

/**
 * Gets called when the render context has been initialized
 *
 * @return 0 = all good, 1 = failed
 */

int on_init() {
    // initialize the font from memory
    if (font_initialize("res/bit_font.ttf", 17) != 0) {
        // return out of the method with an error
        return 1;
    }

    // load all the shaders into the memory
    shader_load_shaders();

    // initialize the renderer
    render_initialize();

    // return 0 meaning initialization was successful
    return 0;
}

/**
 * Gets called every render frame
 */

void on_render() {
    // push new matrix
    glPushMatrix();

    // render text to screen
    render_text(g_window.has_focus == 1 ? "Hello, World!" : "Paused", 5, 5, 1.0f, 0xffa6119e);

    // pop matrix
    glPopMatrix();
}

int main(void) {
    // define a new window handle
    GLFWwindow *window_handle;

    // setup the window settings
    g_window.width = 640;
    g_window.height = 480;
    g_window.has_focus = 1;

    // initialize the library
    if (!glfwInit())
        return -1;

    // disable window resizing
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // create a windowed mode window and its opengl context
    window_handle = glfwCreateWindow(g_window.width, g_window.height, "Pong", NULL, NULL);
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

    // call the init function
    if (on_init() != 0) {
        // terminate the glfw
        glfwTerminate();

        // return out of the method
        return 1;
    }

    // loop until the user closes the window
    while (!glfwWindowShouldClose(window_handle)) {
        // clear the screen color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // setup the 2D rendering
        render_setup_overlay(g_window.width, g_window.height);

        // call the render function
        on_render();

        // swap front and back buffers
        glfwSwapBuffers(window_handle);

        // Poll for and process events
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