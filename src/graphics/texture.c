//
// Created by mat on 6/16/2022.
//

#include "texture.h"
#include <GLFW/glfw3.h>

TEXTURE texture_load(char *name) {
    unsigned int texture_id;
    int texture_width, texture_height;

    // load the texture data
    unsigned char *texture_data = stbi_load(name, &texture_width, &texture_height,
                                            NULL, STBI_rgb_alpha);

    // generate the color texture in the gpo
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    // enable unpack alignment
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // upload the image to the gpu
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture_width,
                 texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);

    // setup the texture parameters
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // free the texture data
    stbi_image_free(texture_data);

    // return the texture
    return (TEXTURE) {
            texture_width,
            texture_height,
            texture_id
    };
}