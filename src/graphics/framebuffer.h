//
// Created by mat on 6/12/2022.
//

#ifndef PONG_CLONE_FRAMEBUFFER_H
#define PONG_CLONE_FRAMEBUFFER_H

#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct {
    unsigned int fbo;
    unsigned int texture;

    int width;
    int height;
} FRAMEBUFFER;

/**
 * Creates a new framebuffer
 *
 * @param width width of the framebuffer
 * @param height height of the framebuffer
 * @return handle of the framebuffer
 */

FRAMEBUFFER *framebuffer_create(int width, int height);

/**
 * Binds the provided framebuffer
 *
 * @param framebuffer framebuffer that you want to bind
 */

void framebuffer_bind(FRAMEBUFFER *framebuffer);

/**
 * Binds the framebuffer color texture
 *
 * @param framebuffer framebuffer that you want to bind the color texture from
 */

void framebuffer_bind_texture(FRAMEBUFFER *framebuffer);

/**
 * Renders the framebuffer
 *
 * @param framebuffer framebuffer that you want to render
 */

void framebuffer_render(FRAMEBUFFER *framebuffer, float x, float y, float width, float height);

/**
 * Unbinds the framebuffer
 */

void framebuffer_unbind();

/**
 * Frees the framebuffer from memory
 *
 * @param framebuffer framebuffer that you want to free
 */

void framebuffer_free(FRAMEBUFFER *framebuffer);

#endif //PONG_CLONE_FRAMEBUFFER_H
