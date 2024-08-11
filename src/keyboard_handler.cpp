/**
 * @file keyboard_handler.cpp
 * @brief Implements keyboard input handling for controlling the application.
 *
 * This file provides the implementation of functions for handling keyboard
 * input to control various aspects of the application, such as camera zoom,
 * orbital visibility, and simulation state.
 */

#include "keyboard_handler.h"

/**
 * @var showOrbits
 * @brief Flag to toggle orbital visibility.
 *
 * This variable indicates whether the orbital paths of celestial bodies
 * are visible or hidden.
 */
bool showOrbits = false;

/**
 * @var cameraDistance
 * @brief Distance of the camera from the target.
 *
 * This variable represents the distance between the camera and the point
 * it is observing, affecting the zoom level.
 */
float cameraDistance = 50.0;

/**
 * @var selectedElement
 * @brief Index of the currently selected celestial body.
 *
 * This variable represents the index of the currently selected planet
 * or celestial body, used for highlighting or focusing. A value of -1
 * indicates no selection.
 */
int selectedElement = -1;

/**
 * @var paused
 * @brief Flag to toggle simulation pause state.
 *
 * This variable indicates whether the simulation is currently paused
 * or running.
 */
bool paused = false;

/**
 * @brief Adjusts the camera zoom level.
 * @param out If true, zooms out; otherwise, zooms in.
 *
 * This function adjusts the camera distance based on the zoom direction.
 * The distance is clamped between 5.0 and 100.0 units.
 */
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

/**
 * @brief Handles keyboard input to control application features.
 * @param key The ASCII code of the pressed key.
 * @param x The X-coordinate of the mouse cursor.
 * @param y The Y-coordinate of the mouse cursor.
 *
 * This function is called when a key is pressed. It processes the key input
 * to perform actions such as zooming the camera, toggling orbital visibility,
 * selecting celestial bodies, and pausing or resuming the simulation.
 */
void keyPressed(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27: // ESC key
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