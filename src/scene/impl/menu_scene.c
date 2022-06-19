//
// Created by mat on 6/11/2022.
//

#include "../scenes.h"

// define the width of the button
static float btn_width = 250;

// define the height of the button
static float btn_height = 30;

// define a pointer where the menu will be stored into
MENU *main_menu = NULL;

/**
 * Gets called when the button is clicked
 *
 * @param button button that was clicked
 */

void menu_action(BUTTON *button) {
    if (strcmp("Play", button->label) == 0) {
        show_scene(&g_game_scene);
    } else if (strcmp("Settings", button->label) == 0) {
        show_scene(&g_settings_scene);
    } else if (strcmp("Quit", button->label) == 0) {
        window_close();
    }
}

/**
 * Gets called when the menu is shown
 */

void menu_show() {
    // define the offset on the y-axis
    float offset = 25;

    // get the width and height of the window
    float x = ((float) window_get_width() - btn_width) / 2.0f;
    float y = ((float) window_get_height() - btn_height) / 2.5f;

    // create a new menu
    main_menu = gui_menu_create();

    // setup the action callback for the menu
    main_menu->on_action = menu_action;

    // add the play button
    BUTTON *play_btn = gui_menu_button(main_menu, "Play", x, y + offset, btn_width, btn_height);
    play_btn->selected = 1;
    offset += btn_height + 15;

    // add the settings button
    gui_menu_button(main_menu, "Settings", x, y + offset, btn_width, btn_height);
    offset += btn_height + 15;

    // add the quit button
    gui_menu_button(main_menu, "Quit", x, y + offset, btn_width, btn_height);
}

/**
 * Gets called when a key is pressed
 *
 * @param key_code key code of the key that was pressed
 * @param mods and mods that might come with the key event
 */

void menu_key_press(int key_code, int mods) {
    // pass the call to the menu
    gui_menu_handle_key(main_menu, key_code, mods);
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
    // render the main menu text
    render_centered_text("Main Menu", width / 2.0f, height / 4.0f);

    // render the menu
    gui_menu_render(main_menu, width, height, mouse_x, mouse_y, time_step);
}

/**
 * Gets called when the menu is closed
 */

void menu_close() {
    // free the menu from memory
    gui_menu_free(main_menu);
}


// define the menu scene
SCENE g_menu_scene = {
        .show       = menu_show,
        .key_press  = menu_key_press,
        .render     = menu_render,
        .close      = menu_close
};