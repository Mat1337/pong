//
// Created by mat on 6/12/2022.
//

#include "ball.h"

/**
 * Renders the ball onto the screen
 *
 * @param ball ball that you want to render
 * @param time_step time since last render call
 */

void ball_render(BALL *ball, float time_step) {
    ball->box.x += ball->vel_x * time_step;
    ball->box.y += ball->vel_y * time_step;

    box_render(&ball->box, 1, (int) 0xffcccccc);
    render_circle(ball->box.x + ball->box.width / 2.0f, ball->box.y + ball->box.height / 2.0f, BALL_RADIUS);
}