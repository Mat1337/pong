//
// Created by mat on 6/11/2022.
//

#include "player.h"


/**
 * Renders the player onto the screen
 *
 * @param player player that you want to render
 * @param width width of the screen
 * @param height height of the screen
 * @param time_step time since the last render tick
 */

void player_render(PLAYER *player, float width, float height, float time_step) {
    // render the outline
    render_set_color_argb((int) 0xffffffff);
    render_quad(player->box.x - 1, player->box.y - 1, player->box.width + 2.0f, player->box.height + 2.0f);

    // render the base
    box_render(&player->box, 0, (int) 0xff888888);

    // if the window does not have focus
    if (!window_has_focus()) {
        // return out of the method
        return;
    }

    // handle the player movement
    if (key_is_down(player->key_up)) {
        player->box.y -= PLAYER_SPEED * time_step;
    } else if (key_is_down(player->key_down)) {
        player->box.y += PLAYER_SPEED * time_step;
    }
}