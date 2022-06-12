//
// Created by mat on 6/12/2022.
//

#include "box.h"

/**
 * Draws the box on the screen
 *
 * @param box box that you want to draw
 * @param outline flag that contains if the box should be rendered as an outline
 * @param color color of the box that you want to draw
 */

void box_render(BOX *box, int outline, int color) {
    render_set_color_argb(color);
    if (outline) {
        render_quad_outline(box->x, box->y, box->width, box->height, 1.0f);
    } else {
        render_quad(box->x, box->y, box->width, box->height);
    }
}
