#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

void keyPressed(unsigned char key, int x, int y);

#endif // KEYBOARD_HANDLER_H