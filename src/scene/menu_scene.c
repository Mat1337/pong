//
// Created by mat on 6/11/2022.
//

#include "scenes.h"
#include "../util/log.h"

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

    // define the offset on the y-axis
    float offset = 0;

    // define the height of the button
    static float btn_height = 30;

    // if the play button was clicked
    if (gui_centered_button("Play", width / 2.0f, height / 2.5f, 250, btn_height)) {

        // show the game scene
        show_scene(&g_game_scene);
    }

    // increment the offset
    offset += btn_height + 15;

    // if the settings button was clicked
    if (gui_centered_button("Settings", width / 2.0f, height / 2.5f + offset, 250, btn_height)) {

        // show the game scene
        show_scene(&g_settings_scene);
    }

    // increment the offset
    offset += btn_height + 15;

    // if the quit button was clicked
    if (gui_centered_button("Quit", width / 2.0f, height / 2.5f + offset, 250, btn_height)) {

        // exit the application
        exit(0);
    }
}


// define the menu scene
SCENE g_menu_scene = {
        .render = menu_render
};