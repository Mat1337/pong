//
// Created by mat on 6/9/2022.
//

#include "graphics/font.h"

void draw_textured_quad(float x, float y, float width, float height) {
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(x, y);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(x, y + height);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(x + width, y + height);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(x + width, y);
    glEnd();
}

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
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, 640, 480);
        glOrtho(0, 640, 480, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glDisable(GL_DEPTH_TEST);

        // get the glyph for letter 'A'
        GLYPH glyph = g_font_glyph['A'];

        // push new matrix
        glPushMatrix();
        glEnable(GL_TEXTURE_2D);

        // enable blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);

        // bind the glyph texture
        glBindTexture(GL_TEXTURE_2D, glyph.texture_id);

        // draw the glyph
        draw_textured_quad(10, 10, 32, 32);

        // unbind the texture
        glBindTexture(GL_TEXTURE_2D, 0);

        // pop matrix
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
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