//
// Created by mat on 6/11/2022.
//

#include "gui.h"

MENU *gui_menu_create() {
    // allocate the memory for the menu
    MENU *menu_ptr = (MENU *) malloc(sizeof(MENU));

    // allocate memory for all the buttons
    menu_ptr->buttons = list_create();

    // return the menu
    return menu_ptr;
}

BUTTON *gui_menu_button(MENU *menu, char *label, float x, float y, float width, float height) {
    // allocate the memory for the button
    BUTTON *button_ptr = (BUTTON *) malloc(sizeof(BUTTON));

    // load the data into the memory
    button_ptr->label = label;
    button_ptr->x = x;
    button_ptr->y = y;
    button_ptr->width = width;
    button_ptr->height = height;
    button_ptr->selected = 0;

    // add the button to the menu
    list_add(menu->buttons, button_ptr);

    // return the pointer to the button
    return button_ptr;
}

void gui_menu_handle_key(MENU *menu, int key_code, int mods) {
    // if the key that was pressed is not up or down or enter
    if (key_code != GLFW_KEY_UP
        && key_code != GLFW_KEY_DOWN
        && key_code != GLFW_KEY_ENTER) {
        // return out of the method
        return;
    }

    // get the iterator for the buttons
    NODE *iterator = menu->buttons->head;

    // keep track of the last iterator
    NODE *last_iterator = NULL;

    // loop through the list
    while (iterator != NULL) {
        // get the current button
        BUTTON *button = (BUTTON *) iterator->data;

        // if the button is selected
        if (button->selected) {
            if (key_code == GLFW_KEY_UP) {
                // deselect the button
                button->selected = 0;

                // if the current iterator is at the start
                if (iterator == menu->buttons->head) {
                    // select the first last item in the list
                    ((BUTTON *) menu->buttons->tail->data)->selected = 1;
                } else {
                    if (last_iterator != NULL && last_iterator->data != NULL) {
                        // else select the previous item in the list
                        ((BUTTON *) last_iterator->data)->selected = 1;
                    }
                }
            } else if (key_code == GLFW_KEY_DOWN) {
                // deselect the button
                button->selected = 0;

                // if the current iterator is at the end
                if (iterator == menu->buttons->tail) {
                    // select the first item in the list
                    ((BUTTON *) menu->buttons->head->data)->selected = 1;
                } else {
                    // else select the next item in the list
                    ((BUTTON *) iterator->next->data)->selected = 1;
                }
            } else {
                // call the on action callback when the enter key is pressed
                menu->on_action(button);
            }

            // return out of the loop
            return;
        }
        // update the last iterator
        last_iterator = iterator;

        // get the next iterator
        iterator = iterator->next;
    }
}

void gui_menu_render(MENU *menu, float width, float height, float mouse_x, float mouse_y, float time_step) {
    // get the iterator for the list
    NODE *iterator = menu->buttons->head;

    // loop through the list
    while (iterator != NULL) {
        // get the current button
        BUTTON *button = (BUTTON *) iterator->data;

        // get the location of the button
        float x = button->x;
        float y = button->y;

        // get the size of the button
        float btn_width = button->width;
        float btn_height = button->height;

        // draw the background of the button
        render_set_color_argb(button->selected ? (int) 0xff00ff00 : (int) 0xff693818);
        render_quad(x, y, btn_width, btn_height);

        // draw the outline of the button
        render_set_color_argb((int) 0xff140401);
        render_quad_outline(x, y, btn_width, btn_height, 1);

        // draw the label of the button
        render_centered_text(button->label, x + btn_width / 2.0f - 3, y + btn_height / 2.0f + 2, 0xffeeeeee);

        // get the next iterator
        iterator = iterator->next;
    }
}

void gui_menu_free(MENU *menu) {
    // free all the buttons from the memory
    list_free(menu->buttons);

    // free the menu itself from the memory
    free(menu);
}