//
// Created by mat on 6/9/2022.
//

#include "util/log.h"
#include "graphics/render.h"
#include "window/window.h"

/**
 * Gets called when the render context has been initialized
 *
 * @return 0 = all good, 1 = failed
 */

int on_init() {
    // initialize the logging system
    if (log_initialize("log.txt") != 0) {
        // return out of the method with an error
        return 1;
    }

    // initialize the font from memory
    if (font_initialize("res/bit_font.ttf", 17) != 0) {
        // return out of the method with an error
        return 1;
    }

    // load all the shaders into the memory
    shader_load_shaders();

    // initialize the renderer
    render_initialize();

    // log to console that the application has been initialized
    LOG_INFO("Application has been %s [%d]", "Initialized", glfwGetTime());

    // return 0 meaning initialization was successful
    return 0;
}

/**
 * Gets called when the mouse is pressed
 *
 * @param button button that was pressed
 * @param x x coordinate of the mouse on the window
 * @param y y coordinate of the mouse on the window
 */

void on_mouse_press(int button, float x, float y) {
}

/**
 * Gets called when the mouse is released
 *
 * @param button button that was pressed
 * @param x x coordinate of the mouse on the window
 * @param y y coordinate of the mouse on the window
 */

void on_mouse_release(int button, float x, float y) {
}

/**
 * Gets called every render frame
 *
 * @param width width of the window
 * @param height height of the window
 * @param mouse_x x coordinate of the mouse in the window
 * @param mouse_y y coordinate of the mouse in the window
 * @param time_step time between two render ticks
 */

void on_render(float width, float height, float mouse_x, float mouse_y, float time_step) {
    // push new matrix
    glPushMatrix();

    // draw the while outline around the screen
    render_set_color(color_get((int) 0xffffffff));
    render_quad_outline(0, 0, width, height, 25.0f);

    // get the time step text
    static char text[256];
    sprintf(text, "TimeStep: %f", time_step);

    // render text to screen
    render_text(text, 10, 10, 0xffa6119e);

    // pop matrix
    glPopMatrix();
}

/**
 * Gets called before the application closes
 */

void on_close() {
    // free font from memory
    font_free();

    // free the logging system
    log_free();
}

int main(void) {
    // initialize the window
    window_initialize();

    // call the init function
    if (on_init() != 0) {
        // close the window
        window_close();

        // return out of the method
        return 1;
    }

    // run the window
    window_run();

    // close the window
    window_close();

    // return out of the application
    return 0;
}