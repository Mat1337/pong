//
// Created by mat on 6/9/2022.
//

#ifndef PONG_CLONE_FONT_H
#define PONG_CLONE_FONT_H

// maximum amount of glyphs that will be loaded for the font
#define MAX_GLYPH_COUNT 256

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <freetype/freetype.h>

typedef struct {
    GLuint texture_id;
    unsigned int width;
    unsigned int height;
    unsigned int advance;
    int bearing_x;
    int bearing_y;
} GLYPH;
extern GLYPH g_font_glyph[MAX_GLYPH_COUNT];

typedef struct {
    int font_size;
    int line_height;
} FONT;
extern FONT g_font;

/**
 * Initializes the font
 *
 * @param name name of the font that you want to load
 * @param font_size size of the font
 * @return 0 = loaded
 */

int font_initialize(char *name, int font_size);

/**
 * Returns the glyph that matches the provided key code
 *
 * @param code key code that you want to get the glyph for
 * @return instance of the glyph struct
 */

GLYPH font_glyph_get(int code);

/**
 * Binds the glyph texture of the provided key code
 *
 * @param code key code that you want to bind the glyph texture for
 */

GLYPH font_glyph_bind(int code);

/**
 * Uploads the font glyph to the GPU
 *
 * @param glyph_bitmap
 * @return id of the texture that was upload to the GPU
 */

unsigned int font_glyph_upload(FT_Bitmap glyph_bitmap);

/**
 * Frees any data that the font takes in the memory
 */

void font_free();

#endif //PONG_CLONE_FONT_H
