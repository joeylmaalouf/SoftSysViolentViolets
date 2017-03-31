#include <GL/glut.h>
#include <iostream>
#include "camera.h"
#include "cursor.h"
#include "util.h"

Camera *camera = new Camera();
Cursor *cursor = new Cursor();
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess[] = {50.0};
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

void update () {
  glutPostRedisplay();
}

void display () {
  camera->display(cursor);
}

void handleInput (unsigned char key, int x, int y) {
  switch (key) {
    case 'x':
      camera->rotateX();
      break;
    case 'y':
      camera->rotateY();
      break;
    case 'z':
      camera->rotateZ();
      break;
    case 'r':
      camera->reset();
      break;
  }
  glutPostRedisplay();
}


void handleSpecialInput (int key, int x, int y) {
  int dx = 0;
  int dy = 0;
  int dz = 0;
  switch (key) {
    case GLUT_KEY_LEFT:
      dx = -1;
      break;
    case GLUT_KEY_RIGHT:
      dx = 1;
      break;
    case GLUT_KEY_DOWN:
      dy = -1;
      break;
    case GLUT_KEY_UP:
      dy = 1;
      break;
    case GLUT_KEY_PAGE_DOWN:
      dz = -1;
      break;
    case GLUT_KEY_PAGE_UP:
      dz = 1;
      break;
  }
  cursor->move(make_tuple(dx, dy, dz));
  glutPostRedisplay();
}

int main (int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(640, 480);
  glutCreateWindow("voxelpaint");

  // Bind functions
  glutIdleFunc(update);
  glutDisplayFunc(display);
  glutKeyboardFunc(handleInput); // https://www.opengl.org/resources/libraries/glut/spec3/node49.html
  glutSpecialFunc(handleSpecialInput);

  // Set up material
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  // Set up lighting
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  // glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  // Set up transparency
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glutMainLoop();
  return 1;
}
