//
// Created by mat on 6/12/2022.
//

#include "framebuffer.h"
#include "render.h"

/**
 * Creates a new framebuffer
 *
 * @param width width of the framebuffer
 * @param height height of the framebuffer
 * @return handle of the framebuffer
 */

FRAMEBUFFER *framebuffer_create(int width, int height) {
    // allocate memory for the framebuffer
    FRAMEBUFFER *framebuffer = (FRAMEBUFFER *) malloc(sizeof(FRAMEBUFFER));

    // set its width & height
    framebuffer->width = width;
    framebuffer->height = height;

    // generate the framebuffer in the gpu
    glGenFramebuffers(1, &framebuffer->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);

    // generate the color texture in the gpo
    glGenTextures(1, &framebuffer->texture);
    glBindTexture(GL_TEXTURE_2D, framebuffer->texture);

    // upload an empty texture to the gpu
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    // setup the texture loading filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // upload the color attachment texture to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebuffer->texture, 0);

    // unbind the frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // return the framebuffer
    return framebuffer;
}

/**
 * Binds the provided framebuffer
 *
 * @param framebuffer framebuffer that you want to bind
 */

void framebuffer_bind(FRAMEBUFFER *framebuffer) {
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->fbo);
}

/**
 * Binds the framebuffer color texture
 *
 * @param framebuffer framebuffer that you want to bind the color texture from
 */

void framebuffer_bind_texture(FRAMEBUFFER *framebuffer) {
    glBindTexture(GL_TEXTURE_2D, framebuffer->texture);
}

/**
 * Renders the framebuffer
 *
 * @param framebuffer framebuffer that you want to render
 */

void framebuffer_render(FRAMEBUFFER *framebuffer) {
    // setup the color masking filter
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);

    // setup the projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, framebuffer->width, 0, framebuffer->height, -1, 1);

    // setup the viewport
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, framebuffer->width, framebuffer->height);
    glDisable(GL_DEPTH_TEST);

    // set the color to white
    glColor4f(1, 1, 1, 1);

    // render the frame buffer
    render_textured_quad(0, 0, (float) framebuffer->width, (float) framebuffer->height);
}

/**
 * Unbinds the framebuffer
 */

void framebuffer_unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/**
 * Frees the framebuffer from memory
 *
 * @param framebuffer framebuffer that you want to free
 */

void framebuffer_free(FRAMEBUFFER *framebuffer) {
    free(framebuffer);
}