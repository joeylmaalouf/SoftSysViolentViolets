#include <GL/glut.h>

#include "camera.h"

Camera *camera = new Camera();

void update() {
  glutPostRedisplay();
}

void display() {
  camera->display();
}

void handleInput(unsigned char key, int x, int y) {
  // switch (key) {
  //   case 'x':
  //     // do something
  //     // break
  // }

  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(640, 480);
  glutCreateWindow("voxelpaint");
  glutIdleFunc(update);
  glutDisplayFunc(display);
  glutKeyboardFunc(handleInput); // https://www.opengl.org/resources/libraries/glut/spec3/node49.html
  glEnable(GL_DEPTH_TEST);
  glutMainLoop();
  return 1;
}
