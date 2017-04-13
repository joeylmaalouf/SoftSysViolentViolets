#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include "camera.h"
#include "util.h"

void drawCube (tuple3i pos, tuple3i col, int draw_flag) {
  float x = (float)get<0>(pos);
  float y = (float)get<1>(pos);
  float z = (float)get<2>(pos);
  int r = get<0>(col);
  int g = get<1>(col);
  int b = get<2>(col);
  int size = 1;

  glPushMatrix();
  glTranslatef(x, y, z);
  glColor4b(r, g, b, 127);

  if (draw_flag == GL_LINES) {
    glutWireCube(size);
  } else {
    glutSolidCube(size);
  }

  glPopMatrix();
}

void Camera::display (World *world) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set up the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  aspect = w / h;
  gluPerspective(fovy, aspect, zNear, zFar);

  // Set up the model matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

  // Set the camera rotation
  glRotated(rotationX, 1.0, 0.0, 0.0);
  glRotated(rotationY, 0.0, 1.0, 0.0);
  glRotated(rotationZ, 0.0, 0.0, 1.0);

  // This is where drawing will happen
  Cursor *cursor = world->getCursor();
  map<tuple3i, Voxel *> grid = world->getGrid();
  for (const auto &p : grid) {
    drawCube(p.first, p.second->getColor(), GL_POLYGON);
  } 

  drawCube(cursor->getPosition(), cursor->getColor(), GL_LINES);
  // Animation uses double-buffering
  glutSwapBuffers();
}

void Camera::rotateX (int degrees) {
    rotationX = fmod(rotationX + degrees, 360);
}

void Camera::rotateY (int degrees) {
    rotationY = fmod(rotationY + degrees, 360);
}

void Camera::rotateZ (int degrees) {
    rotationZ = fmod(rotationZ + degrees, 360);
}

void Camera::zoom (double scalar) {
    eyeX *= scalar;
    eyeY *= scalar;
    eyeZ *= scalar;
}

void Camera::reset () {
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
}
