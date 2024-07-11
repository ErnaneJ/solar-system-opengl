#include "mouse_handler.h"

float cameraAngleX = 0.0;
float cameraAngleY = 0.0;
int lastMouseX = 0;
int lastMouseY = 0;
bool leftButtonPressed = false;

void mouseMotion(int x, int y)
{
  if (leftButtonPressed)
  {
    int dx = x - lastMouseX;
    int dy = y - lastMouseY;

    cameraAngleX += dx * 0.005;
    cameraAngleY += dy * 0.005;

    if (cameraAngleY > 1.5)
      cameraAngleY = 1.5;
    if (cameraAngleY < -1.5)
      cameraAngleY = -1.5;

    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
  }
};

void mouseButton(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
      leftButtonPressed = true;
      lastMouseX = x;
      lastMouseY = y;
    }
    else
    {
      leftButtonPressed = false;
    }
  }
};
