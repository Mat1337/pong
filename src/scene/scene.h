//
// Created by mat on 6/11/2022.
//

#ifndef PONG_CLONE_SCENE_H
#define PONG_CLONE_SCENE_H

#include <stdio.h>

// include the render api
#include "../graphics/render.h"

// define the init function
typedef void(*f_basic)();

// define the mouse function
typedef void(*f_mouse)(int, float, float);

// define the key function
typedef void(*f_key)(int, int);

// define the render function
typedef void (*f_render)(float, float, float, float, float);

typedef struct {
    f_basic show;
    f_mouse mouse_press;
    f_mouse mouse_release;
    f_key key_press;
    f_key key_release;
    f_render render;
    f_basic close;
} SCENE;

#endif //PONG_CLONE_SCENE_H
