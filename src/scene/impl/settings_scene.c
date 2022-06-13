//
// Created by mat on 6/12/2022.
//

#include "../scenes.h"

void settings_render(float width, float height, float mouse_x, float mouse_y, float time_step) {
    int x = 15, y = 15;
    render_text("> Settings", x, y);

    x += 25;
    y += 40;
    render_text("> Player 1", x, y);
    y += 35;
    render_text("Move up:   'W'", x, y);
    y += 35;
    render_text("Move down: 'S'", x, y);

    if (gui_button("Back", 15, height - 45, 150, 30)) {
        show_scene(&g_menu_scene);
    }
}

SCENE g_settings_scene = {
        .render = settings_render
};