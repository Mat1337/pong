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

/**
 * Checks if two boxes have collided
 *
 * @param first_box first box that you want to check
 * @param second_box second box that you want to check
 * @return 1 = collided, 0 = not collided
 */

int box_is_collided(BOX *first_box, BOX *second_box) {
    return first_box->x + first_box->width >= second_box->x
           && first_box->x <= second_box->x + second_box->width
           && first_box->y + first_box->height >= second_box->y
           && first_box->y <= second_box->y + second_box->height;
}
