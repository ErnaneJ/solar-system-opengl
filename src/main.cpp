#define GL_SILENCE_DEPRECATION

#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "stb_image.h"
#include "texture_loader.h"
#include "textures.h"

GLuint texture;

void init()
{
  glEnable(GL_TEXTURE_2D);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  texture = loadTexture(EARTH_TEXTURE);
};

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE);

  glBindTexture(GL_TEXTURE_2D, texture);
  glPushMatrix();
  gluSphere(quad, 1.0, 36, 18);
  glPopMatrix();

  gluDeleteQuadric(quad);
  glutSwapBuffers();
};

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.0, 0.0, -5.0);
};

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Textured Sphere");
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  return 0;
};
