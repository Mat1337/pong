//
// Created by mat on 6/14/2022.
//

#include "settings.h"

// used for storing all the binds for the players
LIST *binds[2];

/**
 * Initializes the settings
 */

void settings_initialize() {
    // create the list that will hold binds for the first player
    binds[0] = list_create();

    // create the list that will hold binds for the second player
    binds[1] = list_create();

    // open the file handle to the settings file
    FILE *file = fopen(SETTINGS_FILE_PATH, "r");

    // if the file failed to open add the default binds
    if (file == NULL) {
        // add the default binds for the first player
        settings_add_bind("Player 1", 1, ACTION_MOVE_UP, GLFW_KEY_W);
        settings_add_bind("Player 1", 1, ACTION_MOVE_DOWN, GLFW_KEY_S);

        // add the default binds for the second player
        settings_add_bind("Player 2", 0, ACTION_MOVE_UP, GLFW_KEY_UP);
        settings_add_bind("Player 2", 0, ACTION_MOVE_DOWN, GLFW_KEY_DOWN);
    } else {
        // read all the binds
        settings_read(file);
    }
}

/**
 * Adds a bind to the settings
 *
 * @param player player that you want to add the bind to
 * @param id id of the player
 * @param action action of the bind
 * @param key_code key code of the bind
 */

void settings_add_bind(char *player, int id, int action, int key_code) {
    // allocate memory for the binds
    BIND *bind = (BIND *) malloc(sizeof(BIND));

    // load the data into the bind
    strcpy(bind->player, player);
    bind->action = action;
    bind->key_code = key_code;

    // add the bind to the list
    list_add(binds[id], bind);
}

/**
 * Gets a bind based on the id and the action
 *
 * @param id id of the player
 * @param action action that you want to get the setting for
 * @return pointer to the bind struct
 */

BIND *settings_get_bind(int id, int action) {
    // get the list of binds based on the id
    LIST *list = binds[id];

    // get the iterator from the list
    NODE *iterator = list->head;

    // loop through the list
    while (iterator != NULL) {
        // get the current bind
        BIND *bind = (BIND *) iterator->data;

        // if the binds action matches the provided action
        if (bind->action == action) {
            // return the bind
            return bind;
        }

        // else continue iterating through the list
        iterator = iterator->next;
    }

    // if nothing was found return NULL
    return NULL;
}

/**
 * Reads all the settings from a file
 *
 * @param file file that you want to read from
 */

void settings_read(FILE *file) {
    // allocate a bind that element gets read into
    BIND *bind = (BIND *) malloc(sizeof(BIND));

    // loop until there is nothing to read in the file
    while (fread(bind, sizeof(BIND), 1, file)) {

        // allocate a bind
        BIND *tmp = (BIND *) malloc(sizeof(BIND));

        // copy all the temp data into the bind
        strcpy(tmp->player, bind->player);
        tmp->action = bind->action;
        tmp->key_code = bind->key_code;

        // and add the bind to the list
        if (strcmp(tmp->player, "Player 1")) {
            list_add(binds[0], tmp);
        } else {
            list_add(binds[1], tmp);
        }
    }

    // free the temp bind data
    free(bind);
}

/**
 * Writes a list to the settings file
 *
 * @param file file that you want to write to
 * @param list list that you want to write
 */

void settings_write(FILE *file, LIST *list) {
    // get the iterator for the list
    NODE *iterator = list->head;

    // loop until the last element in the list
    while (iterator != NULL) {
        // write the node to the file
        fwrite(iterator->data, sizeof(BIND), 1, file);

        // update the iterator to the next iterator
        iterator = iterator->next;
    }
}

/**
 * Saves all the settings
 */

void settings_save() {
    // open the file handle to the settings file
    FILE *file = fopen(SETTINGS_FILE_PATH, "w");

    // if we failed to open handle to the file
    if (file == NULL) {
        // log the error
        LOG_ERROR("Failed to write to file: '%s'", SETTINGS_FILE_PATH);

        // close the window
        window_close();

        // and return out of the function
        return;
    }

    // write the binds for the first player to the file
    settings_write(file, binds[0]);

    // write the binds for the second player to the file
    settings_write(file, binds[1]);

    // close the file
    fclose(file);
}

/**
 * Frees all the data that the settings take up
 */

void settings_free() {
    // save all the settings
    settings_save();

    // free all the lists
    list_free(binds[0]);
    list_free(binds[1]);
}