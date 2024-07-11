#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <cmath>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "stb_image.h"
#include "texture_loader.h"
#include "textures.h"
#include "orbit_radii.h"
#include "planet_radii.h"

float rotationAngle = 0.0;
GLuint sunTexture, mercuryTexture, venusTexture,
    earthTexture, marsTexture, jupiterTexture, saturnTexture,
    uranusTexture, neptuneTexture;

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
}

void drawTexturedSphere(GLuint texture, float radius)
{
  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE);
  glBindTexture(GL_TEXTURE_2D, texture);
  gluSphere(quad, radius, 36, 18);
  gluDeleteQuadric(quad);
}

void drawSun()
{
  glPushMatrix();
  glRotatef(rotationAngle, 0.0, 1.0, 0.0);
  drawTexturedSphere(sunTexture, SUN_RADIUS);
  glPopMatrix();
}

void drawPlanet(GLuint texture, float orbitRadius, float orbitSpeed, float planetRadius)
{
  glPushMatrix();
  glRotatef(rotationAngle * orbitSpeed, 0.0, 1.0, 0.0);
  glTranslatef(orbitRadius, 0.0, 0.0);
  drawTexturedSphere(texture, planetRadius);
  glPopMatrix();
}

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(0.0, 0.0, 50.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  drawSun();

  drawPlanet(mercuryTexture, MERCURY_ORBIT_RADIUS, 4.0, MERCURY_RADIUS);
  drawPlanet(venusTexture, VENUS_ORBIT_RADIUS, 3.0, VENUS_RADIUS);
  drawPlanet(earthTexture, EARTH_ORBIT_RADIUS, 2.0, EARTH_RADIUS);
  drawPlanet(marsTexture, MARS_ORBIT_RADIUS, 1.5, MARS_RADIUS);
  drawPlanet(jupiterTexture, JUPITER_ORBIT_RADIUS, 1.0, JUPITER_RADIUS);
  drawPlanet(saturnTexture, SATURN_ORBIT_RADIUS, 0.8, SATURN_RADIUS);
  drawPlanet(uranusTexture, URANUS_ORBIT_RADIUS, 0.6, URANUS_RADIUS);
  drawPlanet(neptuneTexture, NEPTUNE_ORBIT_RADIUS, 0.5, NEPTUNE_RADIUS);

  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -50.0);
}

void update(int value)
{
  rotationAngle += 0.5;
  if (rotationAngle > 360.0)
    rotationAngle -= 360.0;

  glutPostRedisplay();
  glutTimerFunc(16, update, 0);
}

void keyPressed(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 27: // ESC
    exit(0);
    break;
  default:
    break;
  }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Solar System");

  init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(16, update, 0);

  glutKeyboardFunc(keyPressed);

  glutMainLoop();
  return 0;
}
