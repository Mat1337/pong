//
// Created by mat on 6/9/2022.
//

#include "render.h"
#include "font.h"
#include "shader.h"

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

int render_char_quad(char c, float x, float y) {
    // bind the C glyph
    GLYPH glyph = font_glyph_bind(c);

    // enable blending
    render_blend(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // draw the glyph
    render_textured_quad(x + (float) glyph.bearing_x,
                         y - (float) glyph.bearing_y,
                         (float) glyph.width,
                         (float) glyph.height);

    // return the advance for the current glyph
    return (int) glyph.advance;
}

void render_text(char *text, float x, float y, float scale) {
    // push a new matrix
    glPushMatrix();

    // scale the text
    glScalef(scale, scale, scale);

    // align the texture on the y-axis
    glTranslatef(0, (float) -g_font.line_height / 2.0f, 0);

    // start the texture shader
    shader_start(SHADER_TEXTURE);

    // upload the color to the shader
    shader_uniform_vec4(SHADER_TEXTURE, "u_Color", 1, 1, 1, 1);

    // define an offset that will store the progress of cursor
    float cursor = 0.0f;

    // loop through all characters in the string
    for (int i = 0; i < strlen(text); i++) {

        // render the character and increment the cursor
        cursor += (float) render_char_quad(text[i], x + cursor, y + (float) g_font.line_height);
    }

    // stop the shader
    shader_stop();

    // pop the matrix
    glPopMatrix();
}