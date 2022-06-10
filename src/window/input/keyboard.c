//
// Created by mat on 6/10/2022.
//

#include "keyboard.h"

int pressed_keys[GLFW_KEY_LAST] = {0};

/**
 * Gets called when a key input event triggers
 *
 * @param window window that the event happened op
 * @param key key code of the key that was fired
 * @param scancode scan code of the key
 * @param action action of the event
 * @param mods extra event information
 */

void on_key_input(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (pressed_keys[key] == 0 && action == GLFW_PRESS) {
        on_key_press(key, mods);
    }
    if (pressed_keys[key] == 1 && action == GLFW_RELEASE) {
        on_key_release(key, mods);
    }

    if (action == GLFW_PRESS) {
        pressed_keys[key] = 1;
    } else if (action == GLFW_RELEASE) {
        pressed_keys[key] = 0;
    }
}

/**
 * Gets the name of the key
 *
 * @param key_code key code of the key that you want to get the name of
 * @return name of the key
 */

const char *key_get_name(int key_code) {
    return glfwGetKeyName(key_code, glfwGetKeyScancode(key_code));
}

/**
 * Checks if the key is pressed
 *
 * @param key_code key code of the key that you want to check
 * @return 0 = pressed, 1 = released
 */

int key_is_down(int key_code) {
    return pressed_keys[key_code];
}