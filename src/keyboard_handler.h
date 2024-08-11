/**
 * @file keyboard_handler.h
 * @brief Handles keyboard input for controlling the application.
 *
 * This file declares functions and external variables used for handling keyboard
 * input to control various aspects of the application, such as camera zoom,
 * orbital visibility, and simulation state.
 */

#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>

/**
 * @var showOrbits
 * @brief Flag to toggle orbital visibility.
 *
 * This external boolean variable indicates whether the orbital paths of
 * celestial bodies are visible or hidden.
 */
extern bool showOrbits;

/**
 * @var cameraDistance
 * @brief Distance of the camera from the target.
 *
 * This external float variable represents the distance between the camera
 * and the point it is observing, affecting the zoom level.
 */
extern float cameraDistance;

/**
 * @var zoomExcess
 * @brief Additional zoom factor beyond the default.
 *
 * This external float variable represents the amount of additional zoom
 * applied to the camera view, beyond the default zoom level.
 */
extern float zoomExcess;

/**
 * @var selectedElement
 * @brief Index of the currently selected celestial body.
 *
 * This external integer variable represents the index of the currently
 * selected planet or celestial body, used for highlighting or focusing.
 */
extern int selectedElement;

/**
 * @var paused
 * @brief Flag to toggle simulation pause state.
 *
 * This external boolean variable indicates whether the simulation is currently
 * paused or running.
 */
extern bool paused;

/**
 * @brief Handles keyboard input for controlling the application.
 * @param key The ASCII code of the pressed key.
 * @param x The X-coordinate of the mouse cursor.
 * @param y The Y-coordinate of the mouse cursor.
 *
 * This function is called when a key is pressed. It updates various aspects
 * of the application based on the key input, such as toggling orbital visibility,
 * adjusting camera zoom, selecting celestial bodies, and pausing or resuming
 * the simulation.
 */
void keyPressed(unsigned char key, int x, int y);

#endif // KEYBOARD_HANDLER_H
