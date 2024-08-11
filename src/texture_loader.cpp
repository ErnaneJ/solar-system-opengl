/**
 * @file texture_loader.cpp
 * @brief Implements texture loading functionality.
 *
 * This file provides the implementation of the `loadTexture` function,
 * which loads a texture from a file and generates an OpenGL texture object.
 */

#include "texture_loader.h"

/**
 * @brief Loads a texture from a file and creates an OpenGL texture object.
 * @param filename Path to the texture file.
 * @return The OpenGL texture ID.
 *
 * This function uses the STB image library to load an image from the specified file,
 * creates an OpenGL texture object, and sets its parameters. If the image fails to load,
 * an error message is printed to `std::cerr`.
 */
GLuint loadTexture(const char *filename)
{
  GLuint textureID;
  int width, height, nrChannels;

  // Load image using STB image library
  unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);
  if (data)
  {
    // Generate and bind texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters and upload texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free image data
    stbi_image_free(data);
  }
  else
  {
    std::cerr << "Failed to load texture: " << filename << std::endl;
  }

  // Set texture wrapping and filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  return textureID;
};
