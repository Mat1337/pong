//
// Created by mat on 6/9/2022.
//

#include "graphics/font.h"
#include "graphics/render.h"

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Pong", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // initialize the font from memory
    if (font_initialize("res/bit_font.ttf", 17) != 0) {
        // terminate the glfw
        glfwTerminate();

        // return out of the application
        return 1;
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        // setup the 2D rendering
        render_setup_overlay(640, 480);

        // push new matrix
        glPushMatrix();

        // render text to screen
        render_text("Hello, World!", 5, 5, 2.0f);

        // pop matrix
        glPopMatrix();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // free font from memory
    font_free();

    // terminate the glfw
    glfwTerminate();

    // return out of the application
    return 0;
}