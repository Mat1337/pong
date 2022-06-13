//
// Created by mat on 6/12/2022.
//

#include "../scenes.h"

#define PADDING_X 35
#define PADDING_Y 35

void start_section(char *name, int *x, int *y) {
    *x += PADDING_X;
    *y += PADDING_Y;

    render_text(name, *x, *y);
}

void start_sub_section(char *name, int *x, int *y) {
    start_section(name, x, y);
}

void item(char *name, int *x, int *y) {
    *x += PADDING_X;
    *y += PADDING_Y;

    render_text(name, *x, *y);

    *x -= PADDING_X;
}

void end_sub_section(int *x, int *y) {
    *x -= PADDING_X;
}

void end_section(int *x, int *y) {
    *x -= PADDING_X;
    *y -= PADDING_Y;
}

void settings_render(float width, float height, float mouse_x, float mouse_y, float time_step) {
    int x = 0, y = 0;
    start_section("> Settings", &x, &y);
    {
        y += 25;
        start_sub_section("> Player 1", &x, &y);
        {
            item("Move Up   -> 'W'", &x, &y);
            if (gui_button("Change", width - 155.0f, (float) y, 110, 30)) {

            }
            item("Move Down -> 'S'", &x, &y);
            if (gui_button("Change", width - 155.0f, (float) y, 110, 30)) {

            }
        }
        end_sub_section(&x, &y);
        y += 25;
        start_sub_section("> Player 2", &x, &y);
        {
            item("Move Up   -> 'UP'", &x, &y);
            if (gui_button("Change", width - 155.0f, (float) y, 110, 30)) {

            }
            item("Move Down -> 'DOWN'", &x, &y);
            if (gui_button("Change", width - 155.0f, (float) y, 110, 30)) {

            }
        }
        end_sub_section(&x, &y);
    }
    end_section(&x, &y);

    if (gui_button("Back", 15, height - 45, 150, 30)) {
        show_scene(&g_menu_scene);
    }
}

SCENE g_settings_scene = {
        .render = settings_render
};