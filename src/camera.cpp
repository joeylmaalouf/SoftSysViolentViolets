#include <GL/glut.h>
#include "camera.h"

void drawCube (float x, float y, float z, int draw_flag) {
  float scale = 0.5f;

  glPushMatrix();
  glTranslatef(x, y, z);
  glBegin(draw_flag);
  glColor4f(1.0, 0.0, 0.0, 0.5);

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
  tuple3i pos = cursor->getPosition();
  drawCube(get<0>(pos), get<1>(pos), get<2>(pos), GL_LINES);

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
