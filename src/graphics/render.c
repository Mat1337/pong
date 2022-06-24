//
// Created by mat on 6/9/2022.
//

#include "render.h"
#include "font.h"
#include "shader.h"

// location of the color uniform in the texture shader
int shader_texture_color_uniform;

/**
 * Initializes the renderer
 */

void render_initialize() {
    // start the shader
    shader_start(SHADER_TEXTURE);

    // get the color uniform location for the texture shader
    shader_texture_color_uniform = shader_get_uniform("u_Color");

    // stop the shader when all uniforms are fetched
    shader_stop();
}

/**
 * Sets up the overlay for rendering
 *
 * @param width width of the display
 * @param height height of the display
 */

void render_setup_overlay(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    glDisable(GL_DEPTH_TEST);
    glTranslatef(0, 0, 0);
}

/**
 * Blend the texture
 *
 * @param s_factor source factor of the blend
 * @param d_factor distance factor of the blend
 */

void render_blend(GLenum s_factor, GLenum d_factor) {
    glEnable(GL_BLEND);
    glBlendFunc(s_factor, d_factor);
}

/**
 * Renders a circle
 *
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @param radius radius of the circle
 */

void render_circle(float x, float y, float radius) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 180; i++) {
        glVertex2f(
                x + (radius * cosf((float) i * 6.28f / 180.0f)),
                y + (radius * sinf((float) i * 6.28f / 180.0f))
        );
    }
    glEnd();
}

/**
 * Renders a line on the screen
 *
 * @param x1 first x coordinate of the line
 * @param y1 first y coordinate of the line
 * @param x2 second x coordinate of the line
 * @param y2 second y coordinate of the line
 * @param thickness thickness of the line
 */

void render_line(float x1, float y1, float x2, float y2, float thickness) {
    // enable the texture rendering
    glDisable(GL_TEXTURE_2D);

    // set the line width
    glLineWidth(thickness);

    // begin drawing quads
    glBegin(GL_LINE_LOOP);

    // set the top left corner
    glVertex2f(x1, y1);

    // set the bottom left corner
    glVertex2f(x2, y2);

    // flush the vertices to the gpu
    glEnd();
}


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

void render_dotted_line(float x1, float y1, float x2, float y2, float thickness, GLushort pattern) {
    // enable the texture rendering
    glDisable(GL_TEXTURE_2D);

    // enable the bit attrib
    glPushAttrib(GL_ENABLE_BIT);

    // set the pattern
    glLineStipple(1, pattern);

    // set the line width
    glLineWidth(thickness);

    // enable the line stipple
    glEnable(GL_LINE_STIPPLE);

    // begin drawing quads
    glBegin(GL_LINE_LOOP);

    // set the top left corner
    glVertex2f(x1, y1);

    // set the bottom left corner
    glVertex2f(x2, y2);

    // flush the vertices to the gpu
    glEnd();

    // pop the attrib
    glPopAttrib();
}

/**
 * Renders a textured quad on the screen
 *
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @param width width of the quad
 * @param height height of the quad
 */


void render_textured_quad(float x, float y, float width, float height) {
    // enable the texture rendering
    glEnable(GL_TEXTURE_2D);

    // begin drawing quads
    glBegin(GL_QUADS);

    // set the top left corner
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(x, y);

    // set the bottom left corner
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(x, y + height);

    // set the top right corner
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(x + width, y + height);

    // set the bottom right corner
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(x + width, y);

    // flush the vertices to the gpu
    glEnd();
}

/**
 * Renders a quad on the screen
 *
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @param width width of the quad
 * @param height height of the quad
 */

void render_quad(float x, float y, float width, float height) {
    // enable the texture rendering
    glDisable(GL_TEXTURE_2D);

    // begin drawing quads
    glBegin(GL_QUADS);

    // set the top left corner
    glVertex2f(x, y);

    // set the bottom left corner
    glVertex2f(x, y + height);

    // set the top right corner
    glVertex2f(x + width, y + height);

    // set the bottom right corner
    glVertex2f(x + width, y);

    // flush the vertices to the gpu
    glEnd();
}

/**
 * Renders an outline of the quad on the screen
 *
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @param width width of the quad
 * @param height height of the quad
 * @param thickness thickness of the outline
 */

void render_quad_outline(float x, float y, float width, float height, float thickness) {
    // enable the texture rendering
    glDisable(GL_TEXTURE_2D);

    // set the line width
    glLineWidth(thickness);

    // begin drawing quads
    glBegin(GL_LINE_LOOP);

    // calculate the thickness padding
    float thickess_padding = thickness / 4.0f;

    // set the top left corner
    glVertex2f(x + thickess_padding, y + thickess_padding);

    // set the bottom left corner
    glVertex2f(x + thickess_padding, y + height - thickess_padding);

    // set the top right corner
    glVertex2f(x + width - thickess_padding, y + height - thickess_padding);

    // set the bottom right corner
    glVertex2f(x + width - thickess_padding, y + thickess_padding);

    // flush the vertices to the gpu
    glEnd();
}

/**
 * Renders a character quad on the screen
 *
 * @param c character that you want to render
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @return offset for the cursor
 */

int render_char_quad(char c, float x, float y) {
    // bind the glyph
    GLYPH glyph = font_glyph_bind(c);

    // draw the glyph
    render_textured_quad(x + (float) glyph.bearing_x,
                         y - (float) glyph.bearing_y,
                         (float) glyph.width,
                         (float) glyph.height);

    // return the advance for the current glyph
    return (int) glyph.advance;
}

/**
 * Renders text on the screen
 *
 * @param text text that you want to render
 * @param x x coordinate of the quad
 * @param y y coordinate of the quad
 * @param scale scale of the text
 */

void render_text_params(FONT_ARGS args, int centered) {
    // get the scale from the arguments
    float scale = args.scale ? args.scale : 1.5f;

    // get the color from the arguments
    int argb = args.color ? (int) args.color : (int) 0xffffffff;

    // calculate the correct x & y coordinates
    float x = args.x / scale;
    float y = args.y / scale;

    // if the centered flag is set
    if (centered) {
        // offset the x coordinate by half of the text width
        x -= (float) font_get_text_width(args.text) / 2.0f;

        // offset the y coordinate by half of the text height
        y -= (float) g_font.font_size / 2.0f;
    }

    // get the color values
    COLOR color = color_get(argb);

    // push a new matrix
    glPushMatrix();

    // enable blending
    render_blend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // scale the text
    glScalef(scale, scale, scale);

    // start the texture shader
    shader_start(SHADER_TEXTURE);

    // upload the color to the shader
    shader_uniform_vec4(shader_texture_color_uniform, color.r, color.g, color.b, color.a);

    // define an offset that will store the progress of cursor
    float cursor = x;

    // loop through all characters in the string
    for (int i = 0; i < strlen(args.text); i++) {

        // render the character and increment the cursor
        cursor += (float) render_char_quad(args.text[i], cursor,
                                           y + (float) g_font.line_height / 2.0f);
    }

    // stop the shader
    shader_stop();

    // pop the matrix
    glPopMatrix();
}

/**
 * Sets the current color that will be used to render
 *
 * @param argb argb value of the color that you want to use
 */

void render_set_color_argb(int argb) {
    render_set_color(color_get(argb));
}

/**
 * Sets the current color that will be used to render
 * @param color color that you want to use
 */

void render_set_color(COLOR color) {
    glColor4f(color.r, color.g, color.b, color.a);
}