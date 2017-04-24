#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include "camera.h"
#include "cursor.h"
#include "fileio.h"
#include "world.h"
#include "util.h"
#include <sys/ioctl.h>

#define BOLD "\e[1m"
#define UNBOLD "\e[0m"

Camera *camera = new Camera();
Cursor *cursor = new Cursor();
map<vector<int>, Voxel *> grid;
World *world = new World(grid, cursor, {0, 0, 0});
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess[] = {50.0};
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

void update () {
  glutPostRedisplay();
}

void display () {
  camera->display(world);
}

void displayUsage () {
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  int num_cols = w.ws_col;
  string center_first = string((w.ws_col - 21)/2, ' ');
  string center_second = string((w.ws_col - 24)/2, ' ');
  cout << center_first +"Welcome to Voxelpaint!\n"+
          center_second+ "Voxelpaint usage details:\n"
          BOLD "Move cursor:\n" UNBOLD
               "  l/r arrow keys: x-axis\n"
               "  u/d arrow keys: y-axis\n"
                "  page u/d keys : z-axis\n"
          BOLD  "Place voxel:\n" UNBOLD
                "  mouse l-click: place\n"
                "  mouse r-click: delete\n"
                "  -            : decrease cursor size\n"
                "  =            : increase cursor size\n"
          BOLD  "Camera controls:\n" UNBOLD
                "  w/s: rotate around x-axis\n"
                "  a/d: rotate around y-axis\n"
                "  q/e: rotate around z-axis\n"
                "  z  : zoom in\n"
                "  x  : zoom out\n"
                "  r  : reset\n"
          BOLD "Other controls:\n" UNBOLD
               "  c<red><green><blue>: set color with rgb values\n"
               "  <space><path/to/file>: export current world to .stl\n" 
               "  h: display help menu\n"
               "  crtl-c (in terminal): exit\n";
}

void handleInput (unsigned char key, int x, int y) {
  string filepath;
  string red_s;
  string green_s;
  string blue_s;
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
    case '-':
      cursor->setSize(cursor->getSize() - 1);
      break;
    case '=':
      cursor->setSize(cursor->getSize() + 1);
    case 'h':
      displayUsage();
      break;
    case '1':
      cursor->setShape(1);
      break;
    case '2':
      cursor->setShape(2);
      break;
    case ' ':
      cout << "Please enter a filename for the exported .stl: ";
      cin >> filepath;
      if (filepath != "") {
        exportStl(world, filepath);
      }
      break;
    case 'c':
      cout << "Please enter a red value (0-127): ";
      cin >> red_s;
      cout << "Please enter a green value (0-127): ";
      cin >> green_s;
      cout << "Please enter a blue value (0-127): ";
      cin >> blue_s;
      int red = stoi(red_s);
      int green = stoi(green_s);
      int blue = stoi(blue_s);
      vector<int> color = {red, green, blue};
      cursor->setColor(color);
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
  cursor->move({dx, dy, dz});
  glutPostRedisplay();
}

void handleMouseInput (int button, int state, int x, int y) {
  switch (button) {
    case GLUT_LEFT_BUTTON:
      if (state == GLUT_UP) {
        world->placeVoxels();
      }
      break;
    case GLUT_RIGHT_BUTTON:
      if (state == GLUT_UP) {
        world->eraseVoxels();
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
  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  // Set up lighting
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);

  // Set up color blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE_MINUS_SRC_COLOR);

  // Set up line drawing
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(1.5);

  displayUsage();

  glutMainLoop();
  return 1;
}
