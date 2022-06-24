//
// Created by mat on 6/9/2022.
//

#ifndef PONG_CLONE_RENDER_H
#define PONG_CLONE_RENDER_H

#include <string.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "font.h"
#include "color.h"
#include "shader.h"
#include "framebuffer.h"
#include "texture.h"

#include "../util/math.h"

typedef struct {
    char *text;
    float x;
    float y;
    int color;
    float scale;
} FONT_ARGS;

// define the macro for calling the render text function
#define render_text(...) render_text_params((FONT_ARGS){__VA_ARGS__}, 0)

// define the macro for calling the render text function
#define render_centered_text(...) render_text_params((FONT_ARGS){__VA_ARGS__}, 1)

/**
 * Initializes the renderer
 */

void render_initialize();

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
 * Renders a circle
 *
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @param radius radius of the circle
 */

void render_circle(float x, float y, float radius);

/**
 * Renders a line on the screen
 *
 * @param x1 first x coordinate of the line
 * @param y1 first y coordinate of the line
 * @param x2 second x coordinate of the line
 * @param y2 second y coordinate of the line
 * @param thickness thickness of the line
 */

void render_line(float x1, float y1, float x2, float y2, float thickness);

/**
 * Renders a dotted line on the screen
 *
 * @param x1 first x coordinate of the line
 * @param y1 first y coordinate of the line
 * @param x2 second x coordinate of the line
 * @param y2 second y coordinate of the line
 * @param thickness thickness of the line
 * @param pattern pattern of the dots
 */

void render_dotted_line(float x1, float y1, float x2, float y2, float thickness, GLushort pattern);

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
 * Renders a quad on the screen
 *
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @param width width of the quad
 * @param height height of the quad
 */

void render_quad(float x, float y, float width, float height);

/**
 * Renders an outline of the quad on the screen
 *
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @param width width of the quad
 * @param height height of the quad
 * @param thickness thickness of the outline
 */

void render_quad_outline(float x, float y, float width, float height, float thickness);

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

void render_text_params(FONT_ARGS args, int centered);

/**
 * Sets the current color that will be used to render
 *
 * @param argb argb value of the color that you want to use
 */

void render_set_color_argb(int argb);

/**
 * Sets the current color that will be used to render
 *
 * @param color color that you want to use
 */

void render_set_color(COLOR color);

#endif //PONG_CLONE_RENDER_H
