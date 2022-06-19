//
// Created by mat on 6/11/2022.
//

#ifndef PONG_CLONE_GUI_H
#define PONG_CLONE_GUI_H

#include "../window/window.h"

typedef struct {
    char *label;
    float x;
    float y;
    float width;
    float height;
    int selected;
} BUTTON;

// define the callback function
typedef void(*f_action_callback)(BUTTON *);

typedef struct {
    LIST *buttons;
    f_action_callback on_action;
} MENU;


MENU *gui_menu_create();

BUTTON *gui_menu_button(MENU *menu, char *label, float x, float y, float width, float height);

void gui_menu_handle_key(MENU *menu, int key_code, int mods);

void gui_menu_render(MENU *menu, float width, float height, float mouse_x, float mouse_y, float time_step);

void gui_menu_free(MENU *menu);

#endif //PONG_CLONE_GUI_H
