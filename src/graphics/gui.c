//
// Created by mat on 6/11/2022.
//

#include "gui.h"

// include the mouse api
#include "../window/input/mouse.h"

int gui_button(char *label, float x, float y, float width, float height) {
    // draw the background of the button
    render_set_color(color_get(mouse_is_hovered(x, y, width, height) ? 0x77004477 : 0x66003366));
    render_quad(x, y, width, height);

    // draw the outline of the button
    render_set_color(color_get(0x88006688));
    render_quad_outline(x, y, width, height, 1);

    // draw the label of the button
    render_centered_text(label, x + width / 2.0f - 2, y + height / 2.0f + 2);

    // check if the button was clicked
    return mouse_is_clicked(x, y, width, height);
}

int gui_centered_button(char *label, float x, float y, float width, float height) {
    return gui_button(label, x - width / 2.0f, y - height / 2.0f, width, height);
}