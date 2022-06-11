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
    // if the current scene is valid
    if (current_scene != NULL) {
        // if the close function ptr is valid
        if (current_scene->close) {
            // close the scene
            current_scene->close();
        }
    }

    // update the current scene
    current_scene = scene_ptr;

    // if the show function ptr is valid
    if (current_scene->show) {
        // and show the scene
        current_scene->show();
    }
}

/**
 * Gets the currently displayed scene
 *
 * @return currently displayed scene
 */

SCENE *get_scene() {
    return current_scene;
}