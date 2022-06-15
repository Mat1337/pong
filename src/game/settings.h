//
// Created by mat on 6/14/2022.
//

#ifndef PONG_CLONE_SETTINGS_H
#define PONG_CLONE_SETTINGS_H

#define SETTINGS_FILE_PATH "settings.bin"

#include "../util/log.h"
#include "../util/list.h"
#include "../window/window.h"

enum {
    ACTION_MOVE_UP,
    ACTION_MOVE_DOWN
};

typedef struct {
    char player[256];
    int action;
    int key_code;
} BIND;

/**
 * Initializes the settings
 */

void settings_initialize();

/**
 * Adds a bind to the settings
 *
 * @param player player that you want to add the bind to
 * @param id id of the player
 * @param action action of the bind
 * @param key_code key code of the bind
 */

void settings_add_bind(char *player, int id, int action, int key_code);

/**
 * Gets a bind based on the id and the action
 *
 * @param id id of the player
 * @param action action that you want to get the setting for
 * @return pointer to the bind struct
 */

BIND *settings_get_bind(int id, int action);

/**
 * Reads all the settings from a file
 *
 * @param file file that you want to read from
 */

void settings_read(FILE *file);

/**
 * Writes a list to the settings file
 *
 * @param file file that you want to write to
 * @param list list that you want to write
 */

void settings_write(FILE *file, LIST *list);

/**
 * Saves all the settings
 */

void settings_save();

/**
 * Frees all the data that the settings take up
 */

void settings_free();

#endif //PONG_CLONE_SETTINGS_H
