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

    // make the window start in the middle of the screen
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(g_window.handle, (mode->width - g_window.width) / 2,
                     (mode->height - g_window.height) / 2);

    // load the icon image
    int icon_width, icon_height;
    unsigned char *icon_data = stbi_load("res/app.png", &icon_width, &icon_height,
                                         NULL, STBI_rgb_alpha);

    // set the window icon
    glfwSetWindowIcon(g_window.handle, 1, &((GLFWimage) {
            icon_width,
            icon_height,
            icon_data
    }));

    // free the icon data
    stbi_image_free(icon_data);

    // make current context
    glfwMakeContextCurrent(g_window.handle);

    // initialize the glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        // close the window
        window_close();

        // return out of the method
        return;
    }

    // load all the shaders into the memory
    shader_load_shaders();

    // load the crt shader
    shader_load("crt");

    // start the shader
    shader_start(SHADER_CRT);

    // get the resolution uniform
    g_window.crt_resolution_id = shader_get_uniform("u_Resolution");

    // stop the shader
    shader_stop();

    // setup the window callbacks
    glfwSetWindowSizeCallback(g_window.handle, &on_window_resize);
    glfwSetWindowFocusCallback(g_window.handle, &on_window_focus_change);

    // setup the input callbacks
    glfwSetMouseButtonCallback(g_window.handle, &on_mouse_input);
    glfwSetCursorPosCallback(g_window.handle, &on_mouse_move);
    glfwSetKeyCallback(g_window.handle, &on_key_input);

    // create the framebuffer
    g_window.framebuffer = framebuffer_create(window_get_width(), window_get_height());

    // create the effect framebuffer
    g_window.framebuffer_effect = framebuffer_create(window_get_width(), window_get_height());

    // load the overlay texture
    g_window.overlay_texture = texture_load("res/tv_overlay.png");
}

/**
 * Runs the window loop
 */

void window_run() {
    // loop until the user closes the window
    while (!glfwWindowShouldClose(g_window.handle)) {
        // update the time step
        time_step_update();

        // bind the framebuffer
        framebuffer_bind(g_window.framebuffer);

        // setup the 2D rendering
        render_setup_overlay(g_window.width, g_window.height);

        // get the width & height of the window
        float width = (float) g_window.width;
        float height = (float) g_window.height;

        render_set_color_argb((int) 0xff222222);
        render_quad(0, 0, width, height);

        // call the render function
        on_render(width, height, g_mouse.x, g_mouse.y, time_step_get());

        // unbind the framebuffer
        framebuffer_unbind();

        // bind the effect framebuffer
        framebuffer_bind(g_window.framebuffer_effect);

        // start the shader
        shader_start(SHADER_CRT);

        // upload the resolution to the shader
        shader_uniform_vec2(g_window.crt_resolution_id, width, height);

        // bind the framebuffer texture
        framebuffer_bind_texture(g_window.framebuffer);

        // render the framebuffer
        framebuffer_render(g_window.framebuffer, 0, 0, width, height);

        // stop the shader
        shader_stop();

        // unbind the effect framebuffer
        framebuffer_unbind();

        // bind the framebuffer texture
        framebuffer_bind_texture(g_window.framebuffer_effect);

        // render the framebuffer
        framebuffer_render(g_window.framebuffer_effect, 40, 25, width - 195, height - 50);

        // setup the overlay rendering
        render_setup_overlay((int) width, (int) height);

        // bind the overlay texture
        glBindTexture(GL_TEXTURE_2D, g_window.overlay_texture.id);

        // render the texture
        render_textured_quad(0, 0, width, height);

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

    // free the framebuffer
    framebuffer_free(g_window.framebuffer);
}


/**
 * Closes the window
 */

void window_close() {
    // queue the window for closing
    glfwSetWindowShouldClose(g_window.handle, GL_TRUE);
}