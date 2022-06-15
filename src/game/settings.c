//
// Created by mat on 6/14/2022.
//

#include "settings.h"

LIST *binds[2];

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
        settings_add_bind("Player 1", 0, ACTION_MOVE_UP, GLFW_KEY_W);
        settings_add_bind("Player 1", 0, ACTION_MOVE_DOWN, GLFW_KEY_S);

        // add the default binds for the second player
        settings_add_bind("Player 2", 1, ACTION_MOVE_UP, GLFW_KEY_UP);
        settings_add_bind("Player 2", 1, ACTION_MOVE_DOWN, GLFW_KEY_DOWN);
    } else {
        // read all the binds
        settings_read(file);
    }
}

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

BIND *settings_get_bind(int id, int action) {
    LIST *list = binds[id];

    NODE *iterator = list->head;
    while (iterator != NULL) {
        BIND *bind = (BIND *) iterator->data;
        if (bind->action == action) {
            return bind;
        }
        iterator = iterator->next;
    }

    return NULL;
}

void settings_read(FILE *file) {
    BIND *bind = (BIND *) malloc(sizeof(BIND));
    while (fread(bind, sizeof(BIND), 1, file)) {
        BIND *tmp = (BIND *) malloc(sizeof(BIND));
        strcpy(tmp->player, bind->player);
        tmp->action = bind->action;
        tmp->key_code = bind->key_code;

        if (strcmp(tmp->player, "Player 1")) {
            list_add(binds[0], tmp);
        } else {
            list_add(binds[1], tmp);
        }
    }
}

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

void settings_free() {
    // save all the settings
    settings_save();

    // free all the lists
    list_free(binds[0]);
    list_free(binds[1]);
}