//
// Created by mat on 6/12/2022.
//

#include "../scenes.h"

#define PADDING_X 35
#define PADDING_Y 35

// pointer to the bind that is currently being modified
BIND *current_bind = NULL;

/**
 * Starts a named section
 *
 * @param name name of the section that you want to start
 * @param x pointer to the start x location
 * @param y pointer to the start y location
 */

void start_section(char *name, int *x, int *y) {
    // increment the x & y by the padding amount
    *x += PADDING_X;
    *y += PADDING_Y;

    // render the name of the section
    render_text(name, *x, *y);
}

/**
 * Starts a named sub-section
 *
 * @param name name of the sub section that you want to start
 * @param x pointer to the start x location
 * @param y pointer to the start y location
 */

void start_sub_section(char *name, int *x, int *y) {
    // increment the x by the padding amount
    *y += PADDING_Y / 2.0f;

    // start the section
    start_section(name, x, y);

    // increment the x by the padding amount
    *y += PADDING_Y / 2.0f;
}

void item(BIND *bind, int *x, int *y, float width) {
    // increment the x & y by the padding amount
    *x += PADDING_X;
    *y += PADDING_Y;

    // allocate memory for the string building
    char name[256];

    // render the action string
    sprintf(name, "%s", bind->action == ACTION_MOVE_UP ? "Move Up" : "Move Down");
    render_text(name, *x, *y);

    // render the key name string
    sprintf(name, "->   '%s'", key_get_name(bind->key_code));
    render_text(name, *x + 150, *y);

    // add the change key bind button
    if (gui_button("Change", width - 155.0f, (float) *y - 2.5f, 110, 30)) {
        // update the bind to the current bind
        current_bind = bind;
    }

    // decrement the padding from x-axis
    *x -= PADDING_X;
}

/**
 * Ends a sub-section
 *
 * @param x pointer to the start x location
 * @param y pointer to the start y location
 */

void end_sub_section(int *x, int *y) {
    // subtract the padding from the x
    *x -= PADDING_X;
}

/**
 * Ends a section
 *
 * @param x pointer to the start x location
 * @param y pointer to the start y location
 */

void end_section(int *x, int *y) {
    // subtract the padding from the x & y-axis
    *x -= PADDING_X;
    *y -= PADDING_Y;
}

/**
 * Gets called when ever a key release event happens
 *
 * @param key_code key code of the key that was released
 * @param mods any modifiers that came with the event
 */

void settings_key_release(int key_code, int mods) {
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
        // if the escape key is released
        if (key_code == GLFW_KEY_ESCAPE) {
            // show the main menu scene
            show_scene(&g_menu_scene);
        }
    }
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

    // define the starting position of the ui
    int x = 0, y = 0;

    // start the main settings section
    start_section("> Settings", &x, &y);
    {
        // start the player 1 section
        start_sub_section("> Player 1", &x, &y);
        {
            item(settings_get_bind(1, ACTION_MOVE_UP), &x, &y, width);
            item(settings_get_bind(1, ACTION_MOVE_DOWN), &x, &y, width);
        }
        end_sub_section(&x, &y);

        // start the player 2 section
        start_sub_section("> Player 2", &x, &y);
        {
            item(settings_get_bind(0, ACTION_MOVE_UP), &x, &y, width);
            item(settings_get_bind(0, ACTION_MOVE_DOWN), &x, &y, width);
        }
        end_sub_section(&x, &y);
    }
    end_section(&x, &y);

    // add the back button that takes you to the main menu
    if (gui_button("Back", 15, height - 45, 150, 30)) {
        // if the button is clicked show the main menu scene
        show_scene(&g_menu_scene);
    }
}

SCENE g_settings_scene = {
        .key_release    =   settings_key_release,
        .render         =   settings_render
};