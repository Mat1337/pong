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
    // create the list that will hold all the players
    game->players = list_create();

    // create the list that will hold all the balls
    game->balls = list_create();
}

/**
 * Adds a player to the game
 *
 * @param game game that you want to add player to
 * @param padding horizontal padding
 * @param key_up key that when pressed will move the player up
 * @param key_down key that when pressed will move the player down
 */

void game_add_player(GAME *game, float padding, int key_up, int key_down) {
    // define space in memory for the player
    PLAYER *player = (PLAYER *) malloc(sizeof(PLAYER));

    // setup the player data
    player->box.x = game->players->size == 0 ? padding : (float) window_get_width() - padding * 2;
    player->box.y = ((float) window_get_height() - PLAYER_HEIGHT) / 2.0f;
    player->box.width = PLAYER_WIDTH;
    player->box.height = PLAYER_HEIGHT;

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
 * Adds a ball to the game
 *
 * @param game game that you want to add the ball to
 */

void game_add_ball(GAME *game) {
    // allocate memory for the new ball in the game
    BALL *ball = (BALL *) malloc(sizeof(BALL));

    // set the box width & height
    ball->box.width = BALL_RADIUS * 2;
    ball->box.height = BALL_RADIUS * 2;

    // position the ball in the middle of the screen
    ball->box.x = (((float) window_get_width() - ball->box.width) / 2.0f);
    ball->box.y = (((float) window_get_height() - ball->box.height) / 2.0f);

    // todo :: calculate starting velocities
    ball->vel_x = 350;
    ball->vel_y = -350;

    // add the ball to the list of the balls in the game
    list_add(game->balls, (void *) ball);
}

/**
 * Renders the balls in the game screen
 *
 * @param game game that you want to render
 * @param time_step time since the last render call
 */

void game_render_balls(GAME *game, float time_step) {
    // get the head of the list
    NODE *iterator = game->balls->head;

    // if the iterator is invalid
    if (iterator == NULL) {
        // return out of the method there is nothing to free
        return;
    }

    // loop through the list
    while (iterator != NULL) {
        // render the player
        ball_render((BALL *) iterator->data, time_step);

        // cache the next item
        iterator = iterator->next;
    }
}

/**
 * Checks for any collision
 *
 * @param game handle of the game
 * @param width width of the screen
 * @param height height of the screen
 */

void game_check_collisions(GAME *game, float width, float height) {
    // get the head of the list
    NODE *iterator = game->balls->head;

    // loop through the list
    while (iterator != NULL) {
        // get the current ball
        BALL *ball = iterator->data;

        // check for ball vertical collision with the edge of the screen
        if (ball->box.y < 0 || ball->box.y + ball->box.height > height) {
            // invert the y velocity
            ball->vel_y *= -1;
        }

        // check for horizontal collision
        if (ball->box.x < 0 || ball->box.x + ball->box.width > width) {

            // reset the ball position
            ball->box.x = ((width - ball->box.width) / 2.0f);
            ball->box.y = ((height - ball->box.height) / 2.0f);
        }

        // check for any collision with the players
        game_check_player_collision(game, ball, width, height);

        // update the iterator to the next node
        iterator = iterator->next;
    }
}

/**
 * Checks all the players with
 * collisions with the provided ball
 *
 * @param game handle of the game
 * @param ball ball that you want to check against
 * @param width width of the screen
 * @param height height of the screen
 * @return 1 = collided, 0 = not collided
 */

int game_check_player_collision(GAME *game, BALL *ball, float width, float height) {
    // get the head of the list
    NODE *iterator = game->players->head;

    // loop through the list
    while (iterator != NULL) {
        // get the current player
        PLAYER *player = (PLAYER *) iterator->data;

        // if the player and the ball have collided
        if (box_is_collided(&ball->box, &player->box)) {
            // clamp the ball x position, so it does not go inside the player
            ball->box.x = player->box.x - (ball->box.x > width / 2.0f ? ball->box.width : -player->box.width);

            // invert the x velocity
            ball->vel_x *= -1;
        }

        // update the iterator to the next node
        iterator = iterator->next;
    }

    return 0;
}

/**
 * Stops the game session
 *
 * @param game game that you want to stop the session for
 */

void game_stop(GAME *game) {
    // free the list of players
    list_free(game->players);

    // free the list of balls
    list_free(game->balls);
}