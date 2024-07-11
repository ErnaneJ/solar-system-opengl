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
}

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
}

void drawTexturedSphere(GLuint texture, float radius)
{
  GLUquadric *quad = gluNewQuadric();
  gluQuadricTexture(quad, GL_TRUE);
  glBindTexture(GL_TEXTURE_2D, texture);
  gluSphere(quad, radius, 36, 18);
  gluDeleteQuadric(quad);
}

void drawOrbit(float radius)
{
  glBegin(GL_LINE_LOOP);
  for (int i = 0; i < 360; ++i)
  {
    float theta = i * 3.14159f / 180.0f;
    glVertex3f(radius * cos(theta), 0.0f, radius * sin(theta));
  }
  glEnd();
}

void drawSun(bool withLighting)
{
  if(!withLighting) {
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    return;
  }


  glPushMatrix();
  glRotatef(rotationAngle, 0.0, 1.0, 0.0);
  drawTexturedSphere(sunTexture, SUN_RADIUS);
  glPopMatrix();

  // GLfloat no_emission[] = { 0.0, 0.0, 0.0, 1.0 };
  // glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
}

void drawSaturnRing(float innerRadius, float outerRadius)
{
  GLUquadric* quad = gluNewQuadric();
  glBindTexture(GL_TEXTURE_2D, saturnRingTexture);
  gluQuadricTexture(quad, GL_TRUE);

  glPushMatrix();
  glRotatef(-90.0, 1.0, 0.0, 0.0); // Alinhar o anel no plano correto
  gluDisk(quad, innerRadius, outerRadius, 64, 64); // Desenhar o disco com textura
  glPopMatrix();

  gluDeleteQuadric(quad);
}


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
}
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
    drawPlanet(saturnTexture, SATURN_ORBIT_RADIUS, SATURN_SPEED, SATURN_RADIUS, "SATURN");
    drawPlanet(uranusTexture, URANUS_ORBIT_RADIUS, URANUS_SPEED, URANUS_RADIUS, "URANUS");
    drawPlanet(neptuneTexture, NEPTUNE_ORBIT_RADIUS, NEPTUNE_SPEED, NEPTUNE_RADIUS, "NEPTUNE");
    break;
  }

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
}

void update(int value)
{
  if(!paused)rotationAngle += 0.5;

  glutPostRedisplay();
  glutTimerFunc(16, update, 0);
}

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
}