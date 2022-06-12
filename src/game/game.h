//
// Created by mat on 6/11/2022.
//

#ifndef PONG_CLONE_GAME_H
#define PONG_CLONE_GAME_H

#include "player.h"
#include "../util/list.h"

typedef struct {
    LIST *players;
} GAME;

/**
 * Starts a game session
 *
 * @param game game that you want to start the session for
 * @param player_count amount of players that will play
 */

void game_start(GAME *game);

/**
 * Adds a player to the game
 *
 * @param controls_ptr pointer to the controls that you want to use for the player
 */

void game_add_player(GAME *game, int key_up, int key_down);

/**
 * Renders the players in game to the screen
 *
 * @param game game that you want to render
 * @param time_step time since the last render call
 */

void game_render_players(GAME *game, float time_step);

/**
 * Stops the game session
 *
 * @param game game that you want to stop the session for
 */

void game_stop(GAME *game);

#endif //PONG_CLONE_GAME_H
