//
// Created by mat on 6/12/2022.
//

#include "ball.h"

#define PI 3.14f

/**
 * Renders the ball onto the screen
 *
 * @param ball ball that you want to render
 * @param time_step time since last render call
 */

void ball_render(BALL *ball, float time_step) {
    // render the ball
    render_set_color_argb((int) 0xffffffff);
    render_circle(ball->box.x + ball->box.width / 2.0f, ball->box.y + ball->box.height / 2.0f, BALL_RADIUS);
    render_set_color_argb((int) 0xff999999);
    render_circle(ball->box.x + ball->box.width / 2.0f, ball->box.y + ball->box.height / 2.0f, BALL_RADIUS - 3);

    // if the window does not have focus
    if (!window_has_focus()) {
        // return out of the method
        return;
    }

    // increment the position of the ball based on it's velocity
    ball->box.x += ball->vel_x * time_step;
    ball->box.y += ball->vel_y * time_step;
}

/**
 * Resets the ball data
 *
 * @param ball ball that you want to reset
 * @param width width of the screen
 * @param height height of the screen
 */

void ball_reset(BALL *ball, float width, float height) {
    // invalidate the last hit pointer
    ball->last_hit = NULL;

    // reset the ball speed
    ball->speed = BALL_SPEED;

    // reset the ball position
    ball->box.x = ((width - ball->box.width) / 2.0f);
    ball->box.y = ((height - ball->box.height) / 2.0f);

    // calculate the new velocities
    float angle = rand_float(-PI / 4, PI / 4);
    ball->vel_x = BALL_SPEED * cosf(angle);
    ball->vel_y = BALL_SPEED * sinf(angle);

    // every once in a while switch the velocity direction
    if (rand() > RAND_MAX / 2.0f) {
        ball->vel_x *= -1;
    }
}