//
// Created by mat on 6/9/2022.
//

#include "font.h"

// all the loaded glyphs for the current font
GLYPH g_font_glyph[MAX_GLYPH_COUNT];

// handle of the font struct for the current font
FONT g_font;

// handle of the free type library
FT_Library ft_handle;

int font_initialize(char *name, int font_size) {
    // initialize the freetype library
    int result = FT_Init_FreeType(&ft_handle);
    if (result != 0) {
        return result;
    }

    if (ft_handle == NULL) {
        return 1;
    }

    // load the font face into memory
    FT_Face face;
    result = FT_New_Face(ft_handle, name, 0, &face);
    if (result != 0) {
        FT_Done_FreeType(ft_handle);
        return result;
    }

    // set the font size
    result = FT_Set_Pixel_Sizes(face, 0, font_size);
    if (result != 0) {
        FT_Done_Face(face);
        FT_Done_FreeType(ft_handle);
        return result;
    }

    // loop through all the glyphs
    for (int i = 0; i < MAX_GLYPH_COUNT; i++) {

        // load the character
        if (FT_Load_Char(face, i, FT_LOAD_RENDER) != 0) {
            FT_Done_Face(face);
            FT_Done_FreeType(ft_handle);
            return result;
        }

        // define a new glyph
        GLYPH current_glyph = {
                .width = face->glyph->bitmap.width,
                .height = face->glyph->bitmap.rows,
                .advance = face->glyph->advance.x >> 6,
                .bearing_x = face->glyph->bitmap_left,
                .bearing_y = face->glyph->bitmap_top,
                .texture_id = font_glyph_upload(face->glyph->bitmap)
        };

        // store it in the glyph map
        g_font_glyph[i] = current_glyph;
    }

    // define a new font instance
    FONT font = {
            .font_size = font_size,
            .line_height =
            ((face->ascender + face->height -
              face->descender + face->underline_thickness +
              face->underline_position) >> 6) - 2
    };

    // save the instance as a global instance
    g_font = font;

    // free the face from memory
    FT_Done_Face(face);

    // return 0 meaning everything went all right
    return 0;
}

GLYPH font_glyph_get(int code) {
    // if the provided code is larger than the max glyph count
    if (code > MAX_GLYPH_COUNT) {
        // return the first glyph in the map
        return g_font_glyph[0];
    }

    // else return the glyph that matches the code
    return g_font_glyph[code];
}

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

void font_free() {
    FT_Done_FreeType(ft_handle);
}