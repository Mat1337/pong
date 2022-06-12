//
// Created by mat on 6/11/2022.
//

#include "game.h"
#include "../util/log.h"
#include "../window/window.h"

/**
 * Starts a game session
 *
 * @param game game that you want to start the session for
 * @param player_count amount of players that will play
 */

void game_start(GAME *game) {
    game->players = list_create();
}

/**
 * Adds a player to the game
 *
 * @param controls_ptr pointer to the controls that you want to use for the player
 */

void game_add_player(GAME *game, int key_up, int key_down) {
    // define space in memory for the player
    PLAYER *player = (PLAYER *) malloc(sizeof(PLAYER));

    // setup the player data
    player->x = game->players->size == 0 ? 20 : (float) window_get_width() - 40;
    player->y = ((float) window_get_height() - PLAYER_HEIGHT) / 2.0f;
    player->width = PLAYER_WIDTH;
    player->height = PLAYER_HEIGHT;
    player->key_up = key_up;
    player->key_down = key_down;

    // add the player to the list of the players for the provided game
    list_add(game->players, (void *) player);
}

/**
 * Renders the players from game to the screen
 *
 * @param game game that you want to render
 * @param time_step time since the last render call
 */

void game_render_players(GAME *game, float time_step) {
    // get the head of the list
    NODE *iterator = game->players->head;

    // if the iterator is invalid
    if (iterator == NULL) {
        // return out of the method there is nothing to free
        return;
    }

    // loop through the list
    while (iterator != NULL) {
        // render the player
        player_render((PLAYER *) iterator->data, time_step);

        // cache the next item
        iterator = iterator->next;
    }
}

/**
 * Stops the game session
 *
 * @param game game that you want to stop the session for
 */

void game_stop(GAME *game) {
    // free the list of players
    list_free(game->players);
}