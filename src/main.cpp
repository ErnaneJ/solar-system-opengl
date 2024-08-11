/**
 * @file main.cpp
 * @brief Main entry point for the Solar System simulation application.
 *
 * This file contains the main function and the core rendering logic for
 * the Solar System simulation, including initialization, drawing, and
 * updating the scene. It also handles user input via keyboard and mouse.
 */

#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "stb_image.h"
#include "textures.h"
#include "planet_radii.h"
#include "orbit_radii.h"
#include "planet_speeds.h"

#include "texture_loader.cpp"
#include "mouse_handler.cpp"
#include "keyboard_handler.cpp"

GLuint sunTexture, mercuryTexture, venusTexture, earthTexture, marsTexture, jupiterTexture, saturnTexture, saturnRingTexture, uranusTexture, neptuneTexture;
float rotationAngle = 0.0;

/**
 * @brief Prints the command menu for user instructions.
 *
 * This function prints a menu of commands to the console, providing users
 * with information on how to control the simulation using keyboard and
 * mouse inputs.
 */
void printCommandMenu()
{
  std::cout << "\n--------------------------------------\n";
  std::cout << "🌌 Solar System Simulation Commands 🌌\n";
  std::cout << "--------------------------------------\n";
  std::cout << "❌ Quit: press 'ESC'\n";
  std::cout << "🔄 Toggle orbits: press 'o'\n";
  std::cout << "🔍 Zoom in: press 'w'\n";
  std::cout << "🔎 Zoom out: press 's'\n";
  std::cout << "⏸️ Pause animation: press 'p'\n";
  std::cout << "🖱️ Move camera: press and hold the left mouse button and drag\n";
  std::cout << "🌐 View all elements: press 'A'\n";
  std::cout << "🌍 View individual element:\n";
  std::cout << "  0️⃣ SUN\n";
  std::cout << "  1️⃣ MERCURY\n";
  std::cout << "  2️⃣ VENUS\n";
  std::cout << "  3️⃣ EARTH\n";
  std::cout << "  4️⃣ MARS\n";
  std::cout << "  5️⃣ JUPITER\n";
  std::cout << "  6️⃣ SATURN\n";
  std::cout << "  7️⃣ URANUS\n";
  std::cout << "  8️⃣ NEPTUNE\n";
  std::cout << "\n--------------------------------------\n";
};

/**
 * @brief Initializes OpenGL settings and loads textures.
 *
 * This function sets up OpenGL settings, such as enabling texture mapping
 * and depth testing. It also loads textures for all celestial bodies and
 * prints the command menu.
 */
void init()
{
  glEnable(GL_TEXTURE_2D);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);

  sunTexture = loadTexture(SUN_TEXTURE);
  mercuryTexture = loadTexture(MERCURY_TEXTURE);
  venusTexture = loadTexture(VENUS_TEXTURE);
  earthTexture = loadTexture(EARTH_TEXTURE);
  marsTexture = loadTexture(MARS_TEXTURE);
  jupiterTexture = loadTexture(JUPITER_TEXTURE);
  saturnTexture = loadTexture(SATURN_TEXTURE);
  uranusTexture = loadTexture(URANUS_TEXTURE);
  neptuneTexture = loadTexture(NEPTUNE_TEXTURE);
  saturnRingTexture = loadTexture(SATURN_RING_TEXTURE);

  printCommandMenu();
};

/**
 * @brief Draws a textured sphere with the given texture and radius.
 * @param texture The texture to apply to the sphere.
 * @param radius The radius of the sphere.
 *
 * This function draws a textured sphere using the specified texture and
 * radius, representing a celestial body.
 */
void drawTexturedSphere(GLuint texture, float radius)
{
  glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE);
  glBindTexture(GL_TEXTURE_2D, texture);
  gluSphere(quad, radius, 36, 18);
  gluDeleteQuadric(quad);
};

/**
 * @brief Draws an orbit with the given radius.
 * @param radius The radius of the orbit.
 *
 * This function draws a circular orbit using line loops, representing
 * the path on which a planet revolves around a star.
 */
void drawOrbit(float radius)
{
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < 360; ++i)
  {
    float theta = i * 3.14159f / 180.0f;
    glVertex3f(radius * cos(theta), 0.0f, radius * sin(theta));
  }
  glEnd();
};

/**
 * @brief Draws the sun with optional lighting.
 * @param withLighting If true, lighting effects are enabled; otherwise, they are disabled.
 *
 * This function draws the sun using the sun texture. It also applies a
 * rotation based on the current rotation angle. Lighting effects are applied
 * if specified.
 */
void drawSun(bool withLighting)
{
  if (!withLighting)
  {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    return;
  }

  glPushMatrix();
  glRotatef(rotationAngle, 0.0, 1.0, 0.0);
  drawTexturedSphere(sunTexture, SUN_RADIUS);
  glPopMatrix();
};

/**
 * @brief Draws Saturn's rings.
 * @param innerRadius The inner radius of the rings.
 * @param outerRadius The outer radius of the rings.
 *
 * This function draws Saturn's rings as a series of textured disks. The
 * transparency and spacing of the disks create the appearance of rings.
 */
void drawSaturnRing(float innerRadius, float outerRadius)
{
  int numDisks = 25;
  GLUquadric *quad = gluNewQuadric();
  glBindTexture(GL_TEXTURE_2D, saturnTexture);
  gluQuadricTexture(quad, GL_TRUE);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  float radiusStep = (outerRadius - innerRadius) / numDisks;

  for (int i = 0; i < numDisks; ++i)
  {
    float offset = 0.0;
    if (i % 2 == 0)
    {
      offset = .5;
    }
    float currentInnerRadius = innerRadius + i * radiusStep + offset;
    float currentOuterRadius = currentInnerRadius + radiusStep;

    float alpha = (float)i / (float)(numDisks - 1);

    glColor4f(1.0f, 1.0f, 1.0f, alpha);

    glPushMatrix();
    glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
    gluDisk(quad, currentInnerRadius, currentOuterRadius, 64, 64);
    glPopMatrix();
  }

  glDisable(GL_BLEND);

  gluDeleteQuadric(quad);
};

/**
 * @brief Draws a planet with the specified parameters.
 * @param texture The texture to apply to the planet.
 * @param orbitRadius The radius of the planet's orbit around the sun.
 * @param orbitSpeed The speed of the planet's orbit.
 * @param planetRadius The radius of the planet.
 * @param name The name of the planet (for logging purposes).
 * @param hasRing If true, a ring is drawn around the planet (default is false).
 * @param innerRingRadius The inner radius of the ring (default is 0.0f).
 * @param outerRingRadius The outer radius of the ring (default is 0.0f).
 *
 * This function draws a planet with the specified texture and radius, and
 * optionally draws a ring around the planet if specified.
 */
void drawPlanet(GLuint texture, float orbitRadius, float orbitSpeed, float planetRadius, const char *name, bool hasRing = false, float innerRingRadius = 0.0f, float outerRingRadius = 0.0f)
{
  if (showOrbits)
    drawOrbit(orbitRadius);

  glPushMatrix();
  glRotatef(rotationAngle * orbitSpeed, 0.0, 1.0, 0.0);
  glTranslatef(orbitRadius, 0.0, 0.0);
  drawTexturedSphere(texture, planetRadius);

  if (hasRing)
  {
    drawSaturnRing(innerRingRadius, outerRingRadius);
  }

  glPopMatrix();
};

/**
 * @brief Displays the current frame.
 *
 * This function clears the color and depth buffers, sets up the camera
 * view, and draws all celestial bodies based on the current state. It also
 * handles the selection of individual planets or the entire solar system.
 */
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(cameraDistance * cos(cameraAngleY) * sin(cameraAngleX),
            cameraDistance * sin(cameraAngleY),
            cameraDistance * cos(cameraAngleY) * cos(cameraAngleX),
            0.0, 0.0, 0.0,
            0.0, 1.0, 0.0);

  switch (selectedElement)
  {
  case 0:
    drawSun(true);
    break;
  case 1:
    drawSun(false);
    drawPlanet(mercuryTexture, 0.0, MERCURY_SPEED, MERCURY_RADIUS, "MERCURY");
    break;
  case 2:
    drawSun(false);
    drawPlanet(venusTexture, 0.0, VENUS_SPEED, VENUS_RADIUS, "VENUS");
    break;
  case 3:
    drawSun(false);
    drawPlanet(earthTexture, 0.0, EARTH_SPEED, EARTH_RADIUS, "EARTH");
    break;
  case 4:
    drawSun(false);
    drawPlanet(marsTexture, 0.0, MARS_SPEED, MARS_RADIUS, "MARS");
    break;
  case 5:
    drawSun(false);
    drawPlanet(jupiterTexture, 0.0, JUPITER_SPEED, JUPITER_RADIUS, "JUPITER");
    break;
  case 6:
    drawSun(false);
    drawPlanet(saturnTexture, 0.0, SATURN_SPEED, SATURN_RADIUS, "SATURN", true, SATURN_RADIUS * 1.2f, SATURN_RADIUS * 2.0f);
    break;
  case 7:
    drawSun(false);
    drawPlanet(uranusTexture, 0.0, URANUS_SPEED, URANUS_RADIUS, "URANUS");
    break;
  case 8:
    drawSun(false);
    drawPlanet(neptuneTexture, 0.0, NEPTUNE_SPEED, NEPTUNE_RADIUS, "NEPTUNE");
    break;
  default:
    drawSun(true);
    drawPlanet(mercuryTexture, MERCURY_ORBIT_RADIUS, MERCURY_SPEED, MERCURY_RADIUS, "MERCURY");
    drawPlanet(venusTexture, VENUS_ORBIT_RADIUS, VENUS_SPEED, VENUS_RADIUS, "VENUS");
    drawPlanet(earthTexture, EARTH_ORBIT_RADIUS, EARTH_SPEED, EARTH_RADIUS, "EARTH");
    drawPlanet(marsTexture, MARS_ORBIT_RADIUS, MARS_SPEED, MARS_RADIUS, "MARS");
    drawPlanet(jupiterTexture, JUPITER_ORBIT_RADIUS, JUPITER_SPEED, JUPITER_RADIUS, "JUPITER");
    drawPlanet(saturnTexture, SATURN_ORBIT_RADIUS, SATURN_SPEED, SATURN_RADIUS, "SATURN", true, SATURN_RADIUS * 1.2f, SATURN_RADIUS * 2.0f);
    drawPlanet(uranusTexture, URANUS_ORBIT_RADIUS, URANUS_SPEED, URANUS_RADIUS, "URANUS");
    drawPlanet(neptuneTexture, NEPTUNE_ORBIT_RADIUS, NEPTUNE_SPEED, NEPTUNE_RADIUS, "NEPTUNE");
    break;
  }

  glutSwapBuffers();
};

/**
 * @brief Handles window resizing events.
 * @param w The new width of the window.
 * @param h The new height of the window.
 *
 * This function adjusts the viewport and projection matrix when the window
 * is resized to ensure the correct aspect ratio and perspective.
 */
void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
};

/**
 * @brief Updates the simulation state.
 * @param value Unused parameter for timer function.
 *
 * This function updates the rotation angle for animation and schedules
 * the next update call. It also checks if the simulation is paused or
 * running.
 */
void update(int value)
{
  if (!paused)
    rotationAngle += 0.5;

  glutPostRedisplay();
  glutTimerFunc(16, update, 0);
};

/**
 * @brief Main entry point for the application.
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return 0 on successful execution.
 *
 * This function initializes GLUT, sets up the window, and registers
 * callback functions for display, reshape, keyboard, and mouse events.
 * It then enters the GLUT main loop.
 */
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(1000, 800);
  glutInitWindowPosition(250, 100);
  glutCreateWindow("Solar System");

  init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(16, update, 0); // 60 FPS

  glutKeyboardFunc(keyPressed);

  glutMotionFunc(mouseMotion);
  glutMouseFunc(mouseButton);

  glutMainLoop();

  return 0;
};