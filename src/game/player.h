//
// Created by mat on 6/11/2022.
//

#ifndef PONG_CLONE_PLAYER_H
#define PONG_CLONE_PLAYER_H

#define PLAYER_WIDTH 10
#define PLAYER_HEIGHT 150

#include "../graphics/render.h"
#include "../window/input/keyboard.h"

typedef struct {
    float x;
    float y;
    float width;
    float height;

    int key_up;
    int key_down;
} PLAYER;

/**
 * Renders the player onto the screen
 *
 * @param player player that you want to render
 * @param time_step time since last render call
 */

void player_render(PLAYER *player, float time_step);

#endif //PONG_CLONE_PLAYER_H
