//
// Created by mat on 6/11/2022.
//

#include "scenes.h"

SCENE *current_scene;

/**
 * Shows the provided scene
 *
 * @param scene_ptr pointer to the scene that you want to show
 */

void show_scene(SCENE *scene_ptr) {
    current_scene = scene_ptr;
}

/**
 * Gets the currently displayed scene
 *
 * @return currently displayed scene
 */

SCENE *get_scene() {
    return current_scene;
}