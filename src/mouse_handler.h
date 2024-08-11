/**
 * @file mouse_handler.h
 * @brief Handles mouse input for camera control.
 *
 * This file declares functions and external variables used for handling mouse
 * input to control the camera's position and orientation in the application.
 */

#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

/**
 * @var cameraDistance
 * @brief Distance of the camera from the target.
 *
 * This external variable represents the distance between the camera and the
 * point it is looking at, affecting the zoom level.
 */
extern float cameraDistance;

/**
 * @var cameraAngleX
 * @brief Camera angle around the X-axis.
 *
 * This external variable represents the rotation angle of the camera around
 * the X-axis, affecting the vertical view direction.
 */
extern float cameraAngleX;

/**
 * @var cameraAngleY
 * @brief Camera angle around the Y-axis.
 *
 * This external variable represents the rotation angle of the camera around
 * the Y-axis, affecting the horizontal view direction.
 */
extern float cameraAngleY;

/**
 * @var lastMouseX
 * @brief X-coordinate of the last mouse position.
 *
 * This external variable stores the X-coordinate of the mouse cursor during
 * the last mouse event, used for calculating movement delta.
 */
extern int lastMouseX;

/**
 * @var lastMouseY
 * @brief Y-coordinate of the last mouse position.
 *
 * This external variable stores the Y-coordinate of the mouse cursor during
 * the last mouse event, used for calculating movement delta.
 */
extern int lastMouseY;

/**
 * @var leftButtonPressed
 * @brief State of the left mouse button.
 *
 * This external boolean variable indicates whether the left mouse button is
 * currently pressed, affecting camera control behavior.
 */
extern bool leftButtonPressed;

/**
 * @brief Handles mouse motion events.
 * @param x The X-coordinate of the mouse cursor.
 * @param y The Y-coordinate of the mouse cursor.
 *
 * This function is called when the mouse is moved, allowing updates to the
 * camera's orientation based on the cursor's position.
 */
void mouseMotion(int x, int y);

/**
 * @brief Handles mouse button events.
 * @param button The mouse button that was pressed or released.
 * @param state The state of the mouse button (GLUT_DOWN or GLUT_UP).
 * @param x The X-coordinate of the mouse cursor.
 * @param y The Y-coordinate of the mouse cursor.
 *
 * This function is called when a mouse button is pressed or released, allowing
 * updates to the camera's control state.
 */
void mouseButton(int button, int state, int x, int y);

#endif // MOUSE_HANDLER_H
