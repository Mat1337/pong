//
// Created by mat on 6/9/2022.
//

#include "render.h"
#include "font.h"
#include "shader.h"

// location of the color uniform in the texture shader
int shader_texture_color_uniform;

void render_initialize() {
    // start the shader
    shader_start(SHADER_TEXTURE);

    // get the color uniform location for the texture shader
    shader_texture_color_uniform = shader_get_uniform("u_Color");

    // stop the shader when all uniforms are fetched
    shader_stop();
}

void render_setup_overlay(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, width, height);
    glOrtho(0, width, height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
}

void render_blend(GLenum s_factor, GLenum d_factor) {
    glEnable(GL_BLEND);
    glBlendFunc(s_factor, d_factor);
}

void render_textured_quad(float x, float y, float width, float height) {
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

int render_char_quad(char c, float x, float y) {
    // bind the C glyph
    GLYPH glyph = font_glyph_bind(c);

    // draw the glyph
    render_textured_quad(x + (float) glyph.bearing_x,
                         y - (float) glyph.bearing_y,
                         (float) glyph.width,
                         (float) glyph.height);

    // return the advance for the current glyph
    return (int) glyph.advance;
}

void render_text_params(FONT_ARGS args) {
    // get the scale from the arguments
    float scale = args.scale ? args.scale : 1.0f;

    // get the color from the arguments
    int argb = args.color ? (int) args.color : 0xffffffff;

    // get the color values
    COLOR color = color_get(argb);

    // push a new matrix
    glPushMatrix();

    // enable blending
    render_blend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // scale the text
    glScalef(scale, scale, scale);

    // align the texture on the y-axis
    glTranslatef(0, (float) -g_font.line_height / 2.0f, 0);

    // start the texture shader
    shader_start(SHADER_TEXTURE);

    // upload the color to the shader
    shader_uniform_vec4(shader_texture_color_uniform, color.r, color.g, color.b, color.a);

    // define an offset that will store the progress of cursor
    float cursor = 0.0f;

    // loop through all characters in the string
    for (int i = 0; i < strlen(args.text); i++) {

        // render the character and increment the cursor
        cursor += (float) render_char_quad(args.text[i], args.x + cursor, args.y + (float) g_font.line_height);
    }

    // stop the shader
    shader_stop();

    // pop the matrix
    glPopMatrix();
}