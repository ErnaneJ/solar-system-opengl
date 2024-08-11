#include "keyboard_handler.h"

bool showOrbits = false;
float cameraDistance = 50.0;
int selectedElement = -1;
bool paused = false;

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
  case 'O':
  case 'o':
    showOrbits = !showOrbits;
    break;
  case '0':
    cameraDistance = 10;
    selectedElement = 0;
    break;
  case '1':
    cameraDistance = 10;
    selectedElement = 1;
    break;
  case '2':
    cameraDistance = 10;
    selectedElement = 2;
    break;
  case '3':
    cameraDistance = 10;
    selectedElement = 3;
    break;
  case '4':
    cameraDistance = 10;
    selectedElement = 4;
    break;
  case '5': 
    cameraDistance = 10;
    selectedElement = 5;
    break;
  case '6':
    cameraDistance = 10;
    selectedElement = 6;
    break;
  case '7':
    cameraDistance = 10;
    selectedElement = 7;
    break;
  case '8':
    cameraDistance = 10;
    selectedElement = 8;
    break;
  case 'a':
  case 'A':
    selectedElement = -1;
    break;
  case 'p':
  case 'P':
    paused = !paused;
    break;
  default:
    break;
  }
};