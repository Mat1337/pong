//
// Created by mat on 6/11/2022.
//

#ifndef PONG_CLONE_SCENES_H
#define PONG_CLONE_SCENES_H

// include all the scenes here
#include "impl/menu_scene.h"
#include "impl/game_scene.h"
#include "impl/settings_scene.h"

/**
 * Shows the provided scene
 *
 * @param scene_ptr pointer to the scene that you want to show
 */

void show_scene(SCENE *scene_ptr);

/**
 * Gets the currently displayed scene
 *
 * @return currently displayed scene
 */

SCENE *get_scene();

#endif //PONG_CLONE_SCENES_H
