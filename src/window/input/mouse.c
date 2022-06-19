//
// Created by mat on 6/10/2022.
//

#include "mouse.h"

// used for storing mouse movements
MOUSE g_mouse;

// used for storing the current click point
MOUSE g_click_point;

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
        // cache the click location
        g_click_point.x = g_mouse.x;
        g_click_point.y = g_mouse.y;

        // pass the mouse press call
        on_mouse_press(button, g_mouse.x, g_mouse.y);
    }
    if (action == GLFW_RELEASE) {
        // pass the mouse release call
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

/**
 * Checks if the mouse is in the in the provided bounds
 *
 * @param x x coordinate of the rectangle
 * @param y y coordinate of the rectangle
 * @param width width of the rectangle
 * @param height height of the rectangle
 * @return 0 = true, 1 = false
 */

int mouse_is_hovered(float x, float y, float width, float height) {
    // check if the mouse is inside the bounds
    return g_mouse.x >= x && g_mouse.y >= y
           && g_mouse.x <= (x + width) && g_mouse.y <= (y + height);
}

/**
 * Checks if the mouse has been clicked in the current frame
 * in the provided rectangle
 *
 * @param x x coordinate of the rectangle
 * @param y y coordinate of the rectangle
 * @param width width of the rectangle
 * @param height height of the rectangle
 * @return 0 = false, 1 = true
 */

int mouse_is_clicked(float x, float y, float width, float height) {
    // check if the mouse was clicked inside the provided bounds
    return g_click_point.x >= x && g_click_point.y >= y
           && g_click_point.x <= (x + width) && g_click_point.y <= (y + height);
}

/**
 * Resets the mouse data
 */

void mouse_reset() {
    // invalidate the last click location
    g_click_point.x = -1;
    g_click_point.y = -1;
}