//
// Created by mat on 6/11/2022.
//

#ifndef PONG_CLONE_PLAYER_H
#define PONG_CLONE_PLAYER_H

#define PLAYER_WIDTH 10
#define PLAYER_HEIGHT 150
#define PLAYER_SPEED 400

#include "../util/box.h"
#include "../window/window.h"
#include "../window/input/keyboard.h"

typedef struct {
    BOX box;

    char *name;

    int key_up;
    int key_down;

    int score;
} PLAYER;

/**
 * Renders the player onto the screen
 *
 * @param player player that you want to render
 * @param width width of the screen
 * @param height height of the screen
 * @param time_step time since last render call
 */

void player_render(PLAYER *player, float width, float height, float time_step);

#endif //PONG_CLONE_PLAYER_H
