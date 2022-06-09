//
// Created by mat on 6/9/2022.
//

#ifndef PONG_CLONE_RENDER_H
#define PONG_CLONE_RENDER_H

#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
 * Sets up the overlay for rendering
 *
 * @param width width of the display
 * @param height height of the display
 */

void render_setup_overlay(int width, int height);

/**
 * Blend the texture
 *
 * @param s_factor source factor of the blend
 * @param d_factor distance factor of the blend
 */

void render_blend(GLenum s_factor, GLenum d_factor);

/**
 * Renders a textured quad on the screen
 *
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @param width width of the quad
 * @param height height of the quad
 */

void render_textured_quad(float x, float y, float width, float height);

/**
 * Renders a character quad on the screen
 *
 * @param c character that you want to render
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @return offset for the cursor
 */

int render_char_quad(char c, float x, float y);

/**
 * Renders text on the screen
 *
 * @param text text that you want to render
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @param scale scale of the text
 */

void render_text(char *text, float x, float y, float scale);

#endif //PONG_CLONE_RENDER_H
