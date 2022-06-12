//
// Created by mat on 6/11/2022.
//

#include "player.h"

#include "../util/math.h"

/*
    void line(PLAYER *player, float x_off, float y_off, float x_len, float y_len) {
        float y = player->box.y + player->box.height / 2.0f;
        render_line(player->box.x + x_off, y + y_off, player->box.x + x_off + x_len, y + y_off + y_len, 1.5f);
    }

    void dir(PLAYER *player, float ang, float x_off, float y_off) {
        line(player, x_off, y_off, sinf(math_rad(ang)) * 50, cosf(math_rad(ang)) * 50);
    }
*/

/**
 * Renders the player onto the screen
 *
 * @param player player that you want to render
 * @param width width of the screen
 * @param height height of the screen
 * @param time_step time since the last render tick
 */

void player_render(PLAYER *player, float width, float height, float time_step) {
    // handle the player movement
    if (key_is_down(player->key_up)) {
        player->box.y -= PLAYER_SPEED * time_step;
    } else if (key_is_down(player->key_down)) {
        player->box.y += PLAYER_SPEED * time_step;
    }

    // render the outline
    render_set_color_argb((int) 0xffffffff);
    render_quad(player->box.x - 1, player->box.y - 1, player->box.width + 2.0f, player->box.height + 2.0f);

    /*
        float x_off = player->box.width;
        if (player->box.x > width / 2.0f) {
            x_off = 0;
        }

        // draw the bounce lines
        dir(player, player->box.x > width / 2.0f ? -45 : 45, x_off, -player->box.height / 2.0f);
        dir(player, player->box.x > width / 2.0f ? -90 : 90, x_off, 0);
        dir(player, player->box.x > width / 2.0f ? -135 : 135, x_off, player->box.height / 2.0f);
    */
    // render the base
    box_render(&player->box, 0, (int) 0xff888888);
}