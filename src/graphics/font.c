//
// Created by mat on 6/9/2022.
//

#include "font.h"
#include "../util/log.h"

// all the loaded glyphs for the current font
GLYPH g_font_glyph[MAX_GLYPH_COUNT];

// handle of the font struct for the current font
FONT g_font;

// handle of the free type library
FT_Library ft_handle;

/**
 * Initializes the font
 *
 * @param name name of the font that you want to load
 * @param font_size size of the font
 * @return 0 = loaded
 */

int font_initialize(char *name, int font_size) {
    // initialize the freetype library
    int result = FT_Init_FreeType(&ft_handle);
    if (result != 0) {
        LOG_ERROR("Failed to load the FreeType library");
        return result;
    }

    // load the font face into memory
    FT_Face face;
    result = FT_New_Face(ft_handle, name, 0, &face);
    if (result != 0) {
        LOG_ERROR("Failed to load the font: '%s'", name);
        FT_Done_FreeType(ft_handle);
        return result;
    }

    // set the font size
    result = FT_Set_Pixel_Sizes(face, 0, font_size);
    if (result != 0) {
        LOG_ERROR("Failed to resize the font: '%s', size: '%d'", name, font_size);
        FT_Done_Face(face);
        FT_Done_FreeType(ft_handle);
        return result;
    }

    // loop through all the glyphs
    for (int i = 0; i < MAX_GLYPH_COUNT; i++) {

        // load the character
        if (FT_Load_Char(face, i, FT_LOAD_RENDER) != 0) {
            LOG_ERROR("Failed to load the glyph: '%s', char: '%c', size: '%d'", name, (char) i, font_size);
            FT_Done_Face(face);
            FT_Done_FreeType(ft_handle);
            return result;
        }

        // define a new glyph and store it in the glyph map
        g_font_glyph[i] = (GLYPH) {
                .width = face->glyph->bitmap.width,
                .height = face->glyph->bitmap.rows,
                .advance = face->glyph->advance.x >> 6,
                .bearing_x = face->glyph->bitmap_left,
                .bearing_y = face->glyph->bitmap_top,
                .texture_id = font_glyph_upload(face->glyph->bitmap)
        };
    }

    // define a new font instance and save it as a global instance
    g_font = (FONT) {
            .font_size = font_size,
            .line_height =
            ((face->ascender + face->height -
              face->descender + face->underline_thickness +
              face->underline_position) >> 6) - 2
    };

    // free the face from memory
    FT_Done_Face(face);

    // return 0 meaning everything went all right
    return 0;
}

/**
 * Gets the width of the text
 *
 * @param text text that you want to get the width for
 * @return width of the text
 */

int font_get_text_width(char *text) {
    // width of the text will be stored in this
    int width = 0;

    // loop through all the characters in the string
    for (int i = 0; i < strlen(text); i++) {

        // increment the width by the advance of the glyph
        width += (int) font_glyph_get(text[i]).advance;
    }

    // return the width
    return width;
}

/**
 * Returns the glyph that matches the provided key code
 *
 * @param code key code that you want to get the glyph for
 * @return instance of the glyph struct
 */

GLYPH font_glyph_get(int code) {
    // if the provided code is larger than the max glyph count
    if (code > MAX_GLYPH_COUNT) {
        // return the first glyph in the map
        return g_font_glyph[0];
    }

    // else return the glyph that matches the code
    return g_font_glyph[code];
}

/**
 * Binds the glyph texture of the provided key code
 *
 * @param code key code that you want to bind the glyph texture for
 */

GLYPH font_glyph_bind(int code) {
    // enable the texture rendering
    glEnable(GL_TEXTURE_2D);

    // get the glyph for the provided key
    GLYPH glyph = font_glyph_get(code);

    // bind the glyph texture
    glBindTexture(GL_TEXTURE_2D, glyph.texture_id);

    // return the glyph
    return glyph;
}

/**
 * Uploads the font glyph to the GPU
 *
 * @param glyph_bitmap
 * @return id of the texture that was upload to the GPU
 */

unsigned int font_glyph_upload(FT_Bitmap glyph_bitmap) {
    // define an unsigned int that the texture id will be stored into
    unsigned int id;

    // enable unpack alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // generate the texture id
    glGenTextures(1, &id);

    // bind the texture
    glBindTexture(GL_TEXTURE_2D, id);

    // upload the glyph pixel data to the texture
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            (GLsizei) glyph_bitmap.width,
            (GLsizei) glyph_bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            glyph_bitmap.buffer
    );

    // setup the texture parameters so the image looks pixelated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // return the id of the texture
    return id;
}

/**
 * Frees any data that the font takes in the memory
 */

void font_free() {
    FT_Done_FreeType(ft_handle);
}