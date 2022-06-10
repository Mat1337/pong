//
// Created by mat on 6/10/2022.
//

#include "mouse.h"

// used for storing mouse movements
MOUSE g_mouse;

/**
 * Gets called when them mouse input happens
 *
 * @param window handle of the window
 * @param button button that was pressed
 * @param action action on the input event
  * @param mods mods of the event
*/

void on_mouse_input(GLFWwindow *window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        on_mouse_press(button, g_mouse.x, g_mouse.y);
    }
    if (action == GLFW_RELEASE) {
        on_mouse_release(button, g_mouse.x, g_mouse.y);
    }
}

/**
 * Gets called when them mouse moves in the window
 *
 * @param window handle of the window
 * @param x x coordinate of the mouse on the window
 * @param y y coordinate of the mouse on the window
 */

void on_mouse_move(GLFWwindow *window, double x, double y) {
    g_mouse.x = (float) x;
    g_mouse.y = (float) y;
}