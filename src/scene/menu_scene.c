//
// Created by mat on 6/11/2022.
//

#include "scenes.h"

/**
 * Gets called when the menu is shown
 */

void menu_show() {
}

/**
 * Gets called when the mouse is pressed
 *
 * @param button button that was pressed
 * @param x x coordinate of the mouse on the window
 * @param y y coordinate of the mouse on the window
 */

void menu_mouse_press(int button, float x, float y) {
}

/**
 * Gets called when the mouse is released
 *
 * @param button button that was pressed
 * @param x x coordinate of the mouse on the window
 * @param y y coordinate of the mouse on the window
 */

void menu_mouse_release(int button, float x, float y) {
}

/**
 * Gets called when a key is pressed
 *
 * @param key_code key code of the key that was pressed
 * @param mods and mods that might come with the key event
 */

void menu_key_press(int key_code, int mods) {
    if (key_code == GLFW_KEY_ENTER) {
        show_scene(&g_game_scene);
    }
}

/**
 * Gets called when a key is released
 *
 * @param key_code key code of the key that was released
 * @param mods and mods that might come with the key event
 */

void menu_key_release(int key_code, int mods) {
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

void menu_render(float width, float height, float mouse_x, float mouse_y, float time_step) {
    render_centered_text("Menu Scene", width / 2.0f, height / 2.0f, 0xff00ff00);
}

// define the menu scene
SCENE g_menu_scene = {
        .show = menu_show,
        .mouse_press = menu_mouse_press,
        .mouse_release = menu_mouse_release,
        .key_press = menu_key_press,
        .key_release = menu_key_release,
        .render = menu_render
};