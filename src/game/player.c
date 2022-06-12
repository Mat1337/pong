//
// Created by mat on 6/11/2022.
//

#include "player.h"
#include "../window/window.h"

/**
 * Renders the player onto the screen
 *
 * @param player player that you want to render
 * @param time_step time since the last render tick
 */

void player_render(PLAYER *player, float time_step) {
    // handle the player movement
    if (key_is_down(player->key_up)) {
        player->y -= 250 * time_step;
    } else if (key_is_down(player->key_down)) {
        player->y += 250 * time_step;
    }

    // render the outline
    render_set_color_argb((int) 0xffffffff);
    render_quad(player->x - 1, player->y - 1, player->width + 2.0f, player->height + 2.0f);

    // render the base
    render_set_color_argb((int) 0xff888888);
    render_quad(player->x, player->y, player->width, player->height);
}