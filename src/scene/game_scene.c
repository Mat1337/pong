//
// Created by mat on 6/11/2022.
//

#include "scenes.h"

/**
 * Gets called when the menu is shown
 */

void game_show() {
}

/**
 * Gets called when the mouse is pressed
 *
 * @param button button that was pressed
 * @param x x coordinate of the mouse on the window
 * @param y y coordinate of the mouse on the window
 */

void game_mouse_press(int button, float x, float y) {
}

/**
 * Gets called when the mouse is released
 *
 * @param button button that was pressed
 * @param x x coordinate of the mouse on the window
 * @param y y coordinate of the mouse on the window
 */

void game_mouse_release(int button, float x, float y) {
}

/**
 * Gets called when a key is pressed
 *
 * @param key_code key code of the key that was pressed
 * @param mods and mods that might come with the key event
 */

void game_key_press(int key_code, int mods) {
    // if the escape key was hit
    if (key_code == GLFW_KEY_ESCAPE) {
        // show the menu scene
        show_scene(&g_menu_scene);
    }
}

/**
 * Gets called when a key is released
 *
 * @param key_code key code of the key that was released
 * @param mods and mods that might come with the key event
 */

void game_key_release(int key_code, int mods) {
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

void game_render(float width, float height, float mouse_x, float mouse_y, float time_step) {
    // draw the dotted line in the middle
    float thickness = 1.5f;
    render_set_color(color_get((int) 0xffffffff));
    render_dotted_line((width - thickness) / 2.0f, 35,
                       (width - thickness) / 2.0f, height - 35, thickness, 0x000F);

    render_centered_text("Game Scene", width / 2.0f, height / 2.0f, 0xffff00ff);
}

// define the menu scene
SCENE g_game_scene = {
        .show = game_show,
        .mouse_press = game_mouse_press,
        .mouse_release = game_mouse_release,
        .key_press = game_key_press,
        .key_release = game_key_release,
        .render = game_render
};