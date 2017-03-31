#include <GL/glut.h>
#include "camera.h"

void Camera::display () {
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
  glutSolidTeapot(1);

  // Animation uses double-buffering
  glutSwapBuffers();
}

void Camera::rotateX (int degrees) {
    rotationX += degrees;

    if (rotationX >= 360) {
        rotationX -= 360;
    } else if (rotationX < 0) {
        rotationX += 360;
    }
}

void Camera::rotateY (int degrees) {
    rotationY += degrees;

    if (rotationY >= 360) {
        rotationY -= 360;
    } else if (rotationY < 0) {
        rotationY += 360;
    }
}

void Camera::rotateZ (int degrees) {
    rotationZ += degrees;

    if (rotationZ >= 360) {
        rotationZ -= 360;
    } else if (rotationZ < 0) {
        rotationZ += 360;
    }
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
