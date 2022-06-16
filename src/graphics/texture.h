//
// Created by mat on 6/16/2022.
//

#ifndef PONG_CLONE_TEXTURE_H
#define PONG_CLONE_TEXTURE_H

#include <stdlib.h>
#include <stb_image.h>

#include "../util/list.h"

typedef struct {
    int width;
    int height;
    unsigned int id;
} TEXTURE;

TEXTURE texture_load(char *name);

#endif //PONG_CLONE_TEXTURE_H
