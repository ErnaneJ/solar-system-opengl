#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

extern float cameraDistance;
extern float cameraAngleX;
extern float cameraAngleY;
extern int lastMouseX;
extern int lastMouseY;
extern bool leftButtonPressed;

void mouseMotion(int x, int y);
void mouseButton(int button, int state, int x, int y);
void mouseWheel(int button, int dir, int x, int y);

#endif // MOUSE_HANDLER_H
