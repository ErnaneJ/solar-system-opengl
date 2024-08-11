/**
 * @file texture_loader.h
 * @brief Provides texture loading functionality.
 *
 * This file declares functions and includes necessary libraries for loading
 * textures using the STB image library and OpenGL.
 */

#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

/**
 * @def STB_IMAGE_IMPLEMENTATION
 * @brief Defines implementation of the STB image library.
 *
 * This macro should be defined exactly once in the project to include
 * the implementation of the STB image functions.
 */
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

/**
 * @brief Loads a texture from a file.
 * @param filename Path to the texture file.
 * @return The OpenGL texture ID.
 *
 * This function loads an image from the specified file and generates
 * an OpenGL texture object.
 */
GLuint loadTexture(const char *filename);

#endif // TEXTURE_LOADER_H
