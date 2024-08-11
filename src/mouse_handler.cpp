/**
 * @file mouse_handler.cpp
 * @brief Implements mouse input handling for camera control.
 *
 * This file provides the implementation of functions for handling mouse
 * input, including mouse motion and button events, to control the camera's
 * position and orientation in the application.
 */

#include "mouse_handler.h"

/**
 * @var cameraAngleX
 * @brief Camera angle around the X-axis.
 *
 * This variable represents the rotation angle of the camera around the
 * X-axis, affecting the vertical view direction.
 */
float cameraAngleX = 0.0;

/**
 * @var cameraAngleY
 * @brief Camera angle around the Y-axis.
 *
 * This variable represents the rotation angle of the camera around the
 * Y-axis, affecting the horizontal view direction.
 */
float cameraAngleY = 0.0;

/**
 * @var lastMouseX
 * @brief X-coordinate of the last mouse position.
 *
 * This variable stores the X-coordinate of the mouse cursor during the
 * last mouse event, used for calculating movement delta.
 */
int lastMouseX = 0;

/**
 * @var lastMouseY
 * @brief Y-coordinate of the last mouse position.
 *
 * This variable stores the Y-coordinate of the mouse cursor during the
 * last mouse event, used for calculating movement delta.
 */
int lastMouseY = 0;

/**
 * @var leftButtonPressed
 * @brief State of the left mouse button.
 *
 * This boolean variable indicates whether the left mouse button is currently
 * pressed, affecting camera control behavior.
 */
bool leftButtonPressed = false;

/**
 * @brief Handles mouse motion events to adjust camera orientation.
 * @param x The X-coordinate of the mouse cursor.
 * @param y The Y-coordinate of the mouse cursor.
 *
 * This function is called when the mouse is moved. If the left mouse button
 * is pressed, it updates the camera's orientation based on the cursor's
 * position. The camera angles are clamped to prevent excessive rotation.
 */
void mouseMotion(int x, int y)
{
  if (leftButtonPressed)
  {
    int dx = x - lastMouseX;
    int dy = y - lastMouseY;

    cameraAngleX += dx * 0.005;
    cameraAngleY += dy * 0.005;

    // Clamp cameraAngleY to prevent excessive vertical rotation
    if (cameraAngleY > 1.5)
      cameraAngleY = 1.5;
    if (cameraAngleY < -1.5)
      cameraAngleY = -1.5;

    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();
  }
};

/**
 * @brief Handles mouse button events to toggle camera control.
 * @param button The mouse button that was pressed or released.
 * @param state The state of the mouse button (GLUT_DOWN or GLUT_UP).
 * @param x The X-coordinate of the mouse cursor.
 * @param y The Y-coordinate of the mouse cursor.
 *
 * This function is called when a mouse button is pressed or released. It
 * updates the state of the left mouse button and records the cursor position
 * when the button is pressed.
 */
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