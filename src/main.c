//
// Created by mat on 6/9/2022.
//

#include "util/log.h"
#include "graphics/render.h"
#include "window/window.h"
#include "scene/scenes.h"

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

    // show the menu scene
    show_scene(&g_menu_scene);

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
    // if the window does not have focus
    if (!window_has_focus()) {
        // return out of the method
        return;
    }

    // get the current scene
    SCENE *scene = get_scene();

    // if the scene pointer is valid
    if (scene != NULL) {
        // if the mouse press function ptr is valid
        if (scene->mouse_press) {
            // pass the mouse press call to the scene
            scene->mouse_press(button, x, y);
        }
    }
}

/**
 * Gets called when the mouse is released
 *
 * @param button button that was pressed
 * @param x x coordinate of the mouse on the window
 * @param y y coordinate of the mouse on the window
 */

void on_mouse_release(int button, float x, float y) {
    // if the window does not have focus
    if (!window_has_focus()) {
        // return out of the method
        return;
    }

    // get the current scene
    SCENE *scene = get_scene();

    // if the scene pointer is valid
    if (scene != NULL) {
        // if the mouse release function ptr is valid
        if (scene->mouse_release) {
            // pass the mouse release call to the scene
            scene->mouse_release(button, x, y);
        }
    }
}

/**
 * Gets called when a key is pressed
 *
 * @param key_code key code of the key that was pressed
 * @param mods and mods that might come with the key event
 */

void on_key_press(int key_code, int mods) {
    // if the window does not have focus
    if (!window_has_focus()) {
        // return out of the method
        return;
    }

    // get the current scene
    SCENE *scene = get_scene();

    // if the scene pointer is valid
    if (scene != NULL) {
        // if the key press function ptr is valid
        if (scene->key_press) {
            // pass the key press call to the scene
            scene->key_press(key_code, mods);
        }
    }
}

/**
 * Gets called when a key is released
 *
 * @param key_code key code of the key that was released
 * @param mods and mods that might come with the key event
 */

void on_key_release(int key_code, int mods) {
    // if the window does not have focus
    if (!window_has_focus()) {
        // return out of the method
        return;
    }

    // get the current scene
    SCENE *scene = get_scene();

    // if the scene pointer is valid
    if (scene != NULL) {
        // if the key release function ptr is valid
        if (scene->key_release) {
            // pass the key release call to the scene
            scene->key_release(key_code, mods);
        }
    }
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
    // push a matrix for the current scene
    glPushMatrix();

    // get the current scene
    SCENE *scene = get_scene();

    // if the scene pointer is valid
    if (scene != NULL) {
        // if the render function ptr is valid
        if (scene->render) {
            // pass the render call to the scene
            scene->render(width, height, mouse_x, mouse_y, time_step);
        }
    }

    // pop the scene matrix
    glPopMatrix();

    // push new matrix
    glPushMatrix();

    // get the time step text
    static char text[256];
    sprintf(text, "Fps: %.1f", time_fps_get());

    // render text to screen
    render_text(text, 10, 10, 0xffa6119e);

    // if the window does not have focus
    if (!window_has_focus()) {
        // render the overlay over the game
        render_set_color_argb((int) 0xEE222222);
        render_quad(0, 0, width, height);

        // draw the glowing game paused text
        render_centered_text("Game paused", width / 2.0f + 0.5f, height / 2.0f + 0.5f, 0xff33ff33);
        render_centered_text("Game paused", width / 2.0f - 0.5f, height / 2.0f - 0.5f, 0xff33ff33);
        render_centered_text("Game paused", width / 2.0f, height / 2.0f);
    }

    // pop matrix
    glPopMatrix();
}

/**
 * Gets called before the application closes
 */

void on_close() {
    // get the current scene
    SCENE *scene = get_scene();

    // if the scene pointer is valid
    if (scene != NULL) {
        // if the render function ptr is valid
        if (scene->close) {
            // pass the close call to the scene
            scene->close();
        }
    }

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