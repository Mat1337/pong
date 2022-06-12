//
// Created by mat on 6/11/2022.
//

#include "scenes.h"

// define a pointer to the game struct
GAME game;

/**
 * Gets called when the menu is shown
 */

void game_show() {
    // start the game session for
    game_start(&game);

    // add the first player
    game_add_player(&game, 15, GLFW_KEY_W, GLFW_KEY_S);

    // add the second player
    game_add_player(&game, 15, GLFW_KEY_UP, GLFW_KEY_DOWN);

    // add the ball to the game
    game_add_ball(&game);
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
 * Gets called every render frame
 *
 * @param width width of the window
 * @param height height of the window
 * @param mouse_x x coordinate of the mouse in the window
 * @param mouse_y y coordinate of the mouse in the window
 * @param time_step time between two render ticks
 */

void game_render(float width, float height, float mouse_x, float mouse_y, float time_step) {
    // render the line at the top
    render_set_color(color_get((int) 0xffffffff));
    render_quad(0, 0, width, 5);

    // render the line at the bottom
    render_set_color(color_get((int) 0xffffffff));
    render_quad(0, height - 5, width, 5);

    // draw the dotted line in the middle
    float thickness = 1.5f;
    render_set_color(color_get((int) 0xffffffff));
    render_dotted_line((width - thickness) / 2.0f, 10,
                       (width - thickness) / 2.0f, height - 10, thickness, 0x000F);

    // render all the players from the game
    game_render_players(&game, width, height, time_step);

    // render all the balls from the game
    game_render_balls(&game, time_step);

    // render the score of the game
    game_render_score(&game, width, height, time_step);

    // check for any collisions
    game_check_collisions(&game, width, height);
}

/**
 * Gets called when the game scene closes
 */

void game_close() {
    // stop the game session
    game_stop(&game);
}

// define the menu scene
SCENE g_game_scene = {
        .show           = game_show,
        .key_press      = game_key_press,
        .render         = game_render,
        .close          = game_close
};