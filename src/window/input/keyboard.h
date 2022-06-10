//
// Created by mat on 6/10/2022.
//

#ifndef PONG_CLONE_KEYBOARD_H
#define PONG_CLONE_KEYBOARD_H

#include <GLFW/glfw3.h>

/**
 * Gets called when a key input event triggers
 *
 * @param window window that the event happened op
 * @param key key code of the key that was fired
 * @param scancode scan code of the key
 * @param action action of the event
 * @param mods extra event information
 */

void on_key_input(GLFWwindow *window, int key, int scancode, int action, int mods);

/**
 * Gets the name of the key
 *
 * @param key_code key code of the key that you want to get the name of
 * @return name of the key
 */

const char *key_get_name(int key_code);

/**
 * Checks if the key is pressed
 *
 * @param key_code key code of the key that you want to check
 * @return 0 = pressed, 1 = released
 */

int key_is_down(int key_code);

/**
 * Gets called when a key is pressed
 *
 * @param key_code key code of the key that was pressed
 * @param mods and mods that might come with the key event
 */

extern void on_key_press(int key_code, int mods);

/**
 * Gets called when a key is released
 *
 * @param key_code key code of the key that was released
 * @param mods and mods that might come with the key event
 */

extern void on_key_release(int key_code, int mods);

#endif //PONG_CLONE_KEYBOARD_H
