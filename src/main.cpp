#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include "camera.h"
#include "cursor.h"
#include "world.h"
#include "util.h"

Camera *camera = new Camera();
Cursor *cursor = new Cursor();
map<tuple3i, Voxel *> grid;
World *world = new World(grid, cursor, make_tuple(0, 0, 0));
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess[] = {50.0};
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

void update () {
  glutPostRedisplay();
}

void display () {
  camera->display(world);
}

void handleInput (unsigned char key, int x, int y) {
  switch (key) {
    case 'w':
      camera->rotateX(10);
      break;
    case 's':
      camera->rotateX(-10);
      break;
    case 'a':
      camera->rotateY(10);
      break;
    case 'd':
      camera->rotateY(-10);
      break;
    case 'q':
      camera->rotateZ(10);
      break;
    case 'e':
      camera->rotateZ(-10);
      break;
    case 'z':
      camera->zoom(1.1);
      break;
    case 'x':
      camera->zoom(0.9);
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

void handleMouseInput (int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_UP) {
        world->placeVoxel();
      }
      break;
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_UP) {
        world->eraseVoxel();
      }
      break;
  }
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
  glutKeyboardFunc(handleInput);
  glutSpecialFunc(handleSpecialInput);
  glutMouseFunc(handleMouseInput);

  // Set up material
  glShadeModel(GL_SMOOTH);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  // Set up lighting
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  // glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  // Set up color blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);

  // Set up line drawing
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(1.5);

  glutMainLoop();
  return 1;
}
