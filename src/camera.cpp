#include <GL/glut.h>
#include "camera.h"

void drawCube (tuple3i pos, tuple3i col, int draw_flag) {
  float scale = 0.5f;
  float x = (float)get<0>(pos);
  float y = (float)get<1>(pos);
  float z = (float)get<2>(pos);
  int r = get<0>(col);
  int g = get<1>(col);
  int b = get<2>(col);

  glPushMatrix();
  glTranslatef(x, y, z);
  glBegin(draw_flag);
  glColor4b(r, g, b, 64);

  glVertex3f(-scale, -scale, -scale);
  glVertex3f( scale, -scale, -scale);
  glVertex3f(-scale,  scale, -scale);
  glVertex3f( scale,  scale, -scale);

  glVertex3f(-scale, -scale, -scale);
  glVertex3f(-scale, -scale,  scale);
  glVertex3f( scale, -scale, -scale);
  glVertex3f( scale, -scale,  scale);

  glVertex3f(-scale, -scale,  scale);
  glVertex3f( scale, -scale,  scale);
  glVertex3f(-scale,  scale,  scale);
  glVertex3f( scale,  scale,  scale);

  glVertex3f(-scale,  scale, -scale);
  glVertex3f(-scale,  scale,  scale);
  glVertex3f( scale,  scale, -scale);
  glVertex3f( scale,  scale,  scale);

  glVertex3f( scale,  scale, -scale);
  glVertex3f( scale, -scale, -scale);
  glVertex3f(-scale,  scale, -scale);
  glVertex3f(-scale, -scale, -scale);

  glVertex3f( scale,  scale,  scale);
  glVertex3f( scale, -scale,  scale);
  glVertex3f(-scale,  scale,  scale);
  glVertex3f(-scale, -scale,  scale);

  glEnd();
  glPopMatrix();
}

void Camera::display (Cursor *cursor) {
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
  drawCube(cursor->getPosition(), cursor->getColor(), GL_LINES);

  // Animation uses double-buffering
  glutSwapBuffers();
}

void Camera::rotateX () {
    rotationX += 10;
}

void Camera::rotateY () {
    rotationY += 10;
}

void Camera::rotateZ () {
    rotationZ += 10;
}

void Camera::reset () {
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
}
