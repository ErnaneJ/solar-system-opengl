#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

GLuint loadTexture(const char *filename);

#endif // TEXTURE_LOADER_H