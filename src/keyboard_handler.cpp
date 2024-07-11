#include "keyboard_handler.h"

float cameraDistance = 50.0;

void zoom(bool out)
{
  if (!out)
  {
    cameraDistance -= 1.0;
    if (cameraDistance < 5.0)
      cameraDistance = 5.0;
  }
  else
  {
    cameraDistance += 1.0;
    if (cameraDistance > 100.0)
      cameraDistance = 100.0;
  }
  glutPostRedisplay();
};

void keyPressed(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27: // ESC
    exit(0);
    break;
  case 'W':
  case 'w':
    zoom(false);
    break;
  case 'S':
  case 's':
    zoom(true);
    break;
  default:
    break;
  }
}