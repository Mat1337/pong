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

void settings_initialize();

void settings_add_bind(char *player, int id, int action, int key_code);

BIND *settings_get_bind(int id, int action);

void settings_read(FILE *file);

void settings_write(FILE *file, LIST *list);

void settings_save();

void settings_free();

#endif //PONG_CLONE_SETTINGS_H
