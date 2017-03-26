void Camera::Camera() {
  int w = glutGet(GLUT_WINDOW_WIDTH);
  int h = glutGet(GLUT_WINDOW_HEIGHT);
  Camera::aspect = w / h;
}

void Camera::display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set up the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fovy, aspect, zNear, zFar);

  // Set up the model matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

  // Set the camera rotation
  gluRotated(rotateX, 1.0, 0.0, 0.0);
  gluRotated(rotateY, 0.0, 1.0, 0.0);
  gluRotated(rotateZ, 0.0, 0.0, 1.0);

  // Animation uses double-buffering
  glutSwapBuffers();
}
