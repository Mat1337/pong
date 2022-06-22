//
// Created by mat on 6/12/2022.
//

#include "../scenes.h"

#define PADDING_X 35
#define PADDING_Y 40

// pointer to the bind that is currently being modified
BIND *current_bind = NULL;

// define a pointer where the menu will be stored into
MENU *settings_menu = NULL;

// pointer to the button that takes the player back to main menu
BUTTON *back_btn;

// pointer to the change buttons for the first player
BUTTON *player_1_up_btn;
BUTTON *player_1_down_btn;

// pointer to the change buttons for the second player
BUTTON *player_2_up_btn;
BUTTON *player_2_down_btn;

/**
 * Gets called when the button is clicked
 *
 * @param button button that was clicked
 */

void settings_menu_action(BUTTON *button) {
    if (button == back_btn) {
        show_scene(&g_menu_scene);
    }
}

/**
 * Gets called when the settings scene is shown
 */

void settings_show() {
    // create a new menu
    settings_menu = gui_menu_create();

    // setup the action callback for the menu
    settings_menu->on_action = settings_menu_action;

    // get the width and the height of the window
    float width = (float) window_get_width();
    float height = (float) window_get_height();

    // add the buttons for changing key binds for the first player
    player_1_up_btn = gui_menu_button(settings_menu, "Change", (width - 150.0f) - 70.0f, PADDING_Y * 3 - 5, 150, 30);
    player_1_down_btn = gui_menu_button(settings_menu, "Change", (width - 150.0f) - 70.0f, PADDING_Y * 4 - 5, 150, 30);

    // add the buttons for changing key binds for the second player
    player_2_up_btn = gui_menu_button(settings_menu, "Change", (width - 150.0f) - 70.0f, PADDING_Y * 6 - 5, 150, 30);
    player_2_down_btn = gui_menu_button(settings_menu, "Change", (width - 150.0f) - 70.0f, PADDING_Y * 7 - 5, 150, 30);

    // select the first button
    player_1_up_btn->selected = 1;

    // add the back button
    back_btn = gui_menu_button(settings_menu, "Back", 35, height - 55, 150, 30);
}

/**
 * Gets called when ever a key press event happens
 *
 * @param key_code key code of the key that was pressed
 * @param mods any modifiers that came with the event
 */

void settings_key_press(int key_code, int mods) {
    // if there is a key that is currently being modified
    if (current_bind != NULL) {
        // if the escape key was pressed
        if (key_code == GLFW_KEY_ESCAPE) {
            // cancel the bind modification process
            current_bind = NULL;

            // return out of the method
            return;
        }

        // get the key name of the key that was released
        const char *key_name = key_get_name(key_code);

        // if the pointer to the key name is invalid
        if (key_name == NULL) {
            // return out of the method
            return;
        }

        // else update the key code of the key bind
        current_bind->key_code = key_code;

        // invalidate the current bind pointer
        current_bind = NULL;

        // save the settings to the file
        settings_save();
    } else {
        // pass the call to the menu
        gui_menu_handle_key(settings_menu, key_code, mods);

        // if the escape key is released
        if (key_code == GLFW_KEY_ESCAPE) {
            // show the main menu scene
            show_scene(&g_menu_scene);
        }
    }
}

void settings_render_key(char *description, int key_code, float x, float y) {
    // get the key name
    char key_bind[256];
    sprintf(key_bind, "-> %s", key_get_name(key_code));

    // render the key name
    render_text(description, x, y);
    render_text(key_bind, x * 2.0f, y);
}

void settings_render(float width, float height, float mouse_x, float mouse_y, float time_step) {
    // if there is a bind that's being modified
    if (current_bind != NULL) {
        // render the text that alerts the user to press any key to bind
        render_centered_text("Press any key to bind...", width / 2.0f, height / 2.0f - 25);

        // render the text that tells the user how to cancel the key bind action
        render_centered_text("(ESC for cancel)", width / 2.0f, height / 2.0f);

        // return out of the method
        return;
    }

    // render the settings label
    render_text("> Settings", PADDING_X, PADDING_Y);

    // render the settings label
    render_text("> Player 1", PADDING_X * 2, PADDING_Y * 2);

    // render keybindings for the first player
    settings_render_key("Move up", settings_get_bind(1, ACTION_MOVE_UP)->key_code, PADDING_X * 3.5f, PADDING_Y * 3);
    settings_render_key("Move down", settings_get_bind(1, ACTION_MOVE_DOWN)->key_code, PADDING_X * 3.5f, PADDING_Y * 4);

    // render the settings label
    render_text("> Player 2", PADDING_X * 2, PADDING_Y * 5);

    // render keybindings for the second player
    settings_render_key("Move up", settings_get_bind(0, ACTION_MOVE_UP)->key_code, PADDING_X * 3.5f, PADDING_Y * 6);
    settings_render_key("Move down", settings_get_bind(0, ACTION_MOVE_DOWN)->key_code, PADDING_X * 3.5f, PADDING_Y * 7);

    // render the menu
    gui_menu_render(settings_menu, width, height, mouse_y, mouse_y, time_step);
}

/**
 * Gets called when the settings scene is closed
 */

void settings_close() {
    // free the menu from memory
    gui_menu_free(settings_menu);
}

SCENE g_settings_scene = {
        .show           =   settings_show,
        .key_press      =   settings_key_press,
        .render         =   settings_render,
        .close          =   settings_close
};