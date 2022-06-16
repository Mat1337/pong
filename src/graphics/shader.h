//
// Created by mat on 6/9/2022.
//

#ifndef PONG_CLONE_SHADER_H
#define PONG_CLONE_SHADER_H

// size of the buffer that chunks of file data get read into
#define MAX_READ_BUFFER 1024 * 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef enum {
    SHADER_TEXTURE = 0,
    SHADER_CRT,
    SHADER_RESERVED
} SHADER;

/**
 * Loads all the shaders into memory
 */

void shader_load_shaders();

/**
 * Starts the provided shader program
 *
 * @param shader shader that you want to start
 */

void shader_start(SHADER shader);

/**
 * Uploads vector of 4 floats
 *
 * @param x x value vector
 * @param y y value vector
 * @param z z value vector
 * @param w w value vector
 */

void shader_uniform_vec4(int uniform, float x, float y, float z, float w);

/**
 * Uploads vector of 2 floats
 *
 * @param x x value vector
 * @param y y value vector
 */

void shader_uniform_vec2(int uniform, float x, float y);

/**
 * Gets a uniform location based on its name
 *
 * @param name name of the uniform
 * @return location of the uniform in the shaders
 */

int shader_get_uniform(char *name);

/**
 * Stops any active shaders
 */

void shader_stop();

/**
 * Loads a shader from the resource
 *
 * @param name name of the shader that you want to load
 * @return id of the shader that was created
 */

int shader_load(char *name);

/**
 * Loads the shader from the vertex & fragment shader files
 *
 * @param vertex path to the vertex shader file
 * @param fragment path to the fragment shader file
 * @return id of the shader that was created
 */

int shader_load_from_path(char *vertex, char *fragment);

/**
 * Creates a shader from the source
 *
 * @param source source of the shader that you want to create
 * @param type type of shader that it is
 * @return id of the shader that was created
 */

int shader_create(char *source, int type);

/**
 * Reads the source code of the shader
 *
 * @param path path to the shader file that you want to read
 * @return source code of the shader
 */

char *shader_read_source(char *path);

/**
 * Gets the resource path to the shader file
 *
 * @param name name of the shader that you want to get
 * @param type type of the shader that you want to get
 * @return path in the resource to the shader
 */

char *shader_get_path(char *path, char *name, char *type);

#endif //PONG_CLONE_SHADER_H
