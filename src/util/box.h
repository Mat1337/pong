//
// Created by mat on 6/12/2022.
//

#ifndef PONG_CLONE_BOX_H
#define PONG_CLONE_BOX_H

#include "../graphics/render.h"

typedef struct {
    float x;
    float y;

    float width;
    float height;
} BOX;

/**
 * Draws the box on the screen
 *
 * @param box box that you want to draw
 * @param outline flag that contains if the box should be rendered as an outline
 * @param color color of the box that you want to draw
 */

void box_render(BOX *box, int outline, int color);

/**
 * Checks if two boxes have collided
 *
 * @param first_box first box that you want to check
 * @param second_box second box that you want to check
 * @return 1 = collided, 0 = not collided
 */

int box_is_collided(BOX *first_box, BOX *second_box);

#endif //PONG_CLONE_BOX_H
