#include "camera.h"
#include "util.h"

void drawCube (vector<int> pos, vector<int> color, int size, int draw_flag) {
  float x = static_cast<float>(pos[0]);
  float y = static_cast<float>(pos[1]);
  float z = static_cast<float>(pos[2]);

  glPushMatrix();
  glTranslatef(x, y, z);
  glColor4b(color[0], color[1], color[2], 127);

  if (draw_flag == GL_LINES) {
    glEnable(GL_BLEND);
    glutWireCube(size);
  } else {
    glDisable(GL_BLEND);
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

  // Draw the voxels and cursor in the world
  map<vector<int>, Voxel *> grid = world->getGrid();
  for (const auto &p : grid) {
    drawCube(p.first, p.second->getColor(), 1, GL_POLYGON);
  }

  Cursor *cursor = world->getCursor();
  int radius = cursor->getSize();
  drawCube(cursor->getPosition(), cursor->getColor(), 2 * radius - 1, GL_LINES);

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

void Camera::reset () {
    rotationX = 0;
    rotationY = 0;
    rotationZ = 0;
}

void Camera::zoom (double scalar) {
    eyeX *= scalar;
    eyeY *= scalar;
    eyeZ *= scalar;
}
