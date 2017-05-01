#include <iostream>
#include <sys/ioctl.h>

#include "camera.h"
#include "cursor.h"
#include "fileio.h"
#include "util.h"
#include "world.h"

#define BOLD "\e[1m"
#define UNBOLD "\e[0m"

Camera *camera = new Camera();
Cursor *cursor = new Cursor();
map<vector<int>, Voxel *> grid;
World *world = new World(grid, cursor, {0, 0, 0});

// Materials
// OpenGL uses the Phong model https://en.wikipedia.org/wiki/Phong_reflection_model
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat mat_shininess[] = {50.0};

// The position of the light in the scene
GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};

/*
 * Idle function -- called by glutIdleFunc.
 */
void update () {
  glutPostRedisplay();
}


/*
 * Display function -- called by glutDisplayFunc.
 */
void display () {
  camera->display(world);
}

/*
 * Prints the help string.
 */
void displayUsage () {
  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  string center_first = string((w.ws_col - 21)/2, ' ');
  string center_second = string((w.ws_col - 24)/2, ' ');
  cout << center_first  + "Welcome to Voxelpaint!\n" +
          center_second + "Voxelpaint usage details:\n"
           BOLD "Move cursor:\n" UNBOLD
                "  l/r arrow keys: x-axis\n"
                "  u/d arrow keys: y-axis\n"
                "  page u/d keys : z-axis\n"
           BOLD "Place voxel:\n" UNBOLD
                "  <space> : place\n"
                "  <delete>: delete\n"
                "  -       : decrease cursor size\n"
                "  =       : increase cursor size\n"
           BOLD "Shapes:\n" UNBOLD
                "  1: sphere\n"
                "  2: cube\n"
           BOLD "History:\n" UNBOLD
                "  u: undo\n"
                "  ctrl-u: redo\n"
           BOLD "Camera controls:\n" UNBOLD
                "  w/s: rotate around x-axis\n"
                "  a/d: rotate around y-axis\n"
                "  q/e: rotate around z-axis\n"
                "  z  : zoom in\n"
                "  x  : zoom out\n"
                "  r  : reset\n"
           BOLD "Other controls:\n" UNBOLD
                "  c<red><green><blue>: set color with rgb values\n"
                "  k<path/to/file>    : export current world to .3dp\n"
                "  l<path/to/file>    : load existing world from .3dp\n"
                "  f<path/to/file>    : export current world to .stl\n"
                "  h                  : display help menu\n"
                "  ctrl-c             : exit\n";
}

/*
 * Standard key input handler -- called by glutKeyboardFunc.
 */
void handleInput (unsigned char key, int x, int y) {
  string filepath;
  string red_s, green_s, blue_s;
  int red, green, blue;
  int ctrl = glutGetModifiers() & GLUT_ACTIVE_CTRL;
  if (ctrl) {
    key += 96;  // control key subtracts 96 from key value, for some reason (?)
  }

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
      break;
    case 'h':
      displayUsage();
      break;
    case '1':
      cursor->setShape(0);
      break;
    case '2':
      cursor->setShape(1);
      break;
    case 'u':
      if (ctrl) {
        world->redo();
      } else {
        world->undo();
      }
      break;
    case 'c':
      if (ctrl) {
          exit(0);
      } else {
        cout << "Please enter a red value (0-127): ";
        cin >> red_s;
        cout << "Please enter a green value (0-127): ";
        cin >> green_s;
        cout << "Please enter a blue value (0-127): ";
        cin >> blue_s;
        red = stoi(red_s);
        green = stoi(green_s);
        blue = stoi(blue_s);
        cursor->setColor({red, green, blue});
      }
        break;
    case ' ':
      world->placeVoxels();
      break;
    case 8:
      // backspace
      world->eraseVoxels();
      break;
    case 127:
      // delete
      world->eraseVoxels();
      break;
    case 'f':
      cout << "Please enter a filename for the exported .stl: ";
      cin >> filepath;
      if (filepath != "") {
        exportStl(world, filepath);
      }
      break;
    case 'k':
      cout << "Please enter a filename for the exported .3dp: ";
      cin >> filepath;
      if (filepath != "") {
        export3dp(world, filepath);
      }
      break;
    case 'l':
      cout << "Please enter the filename of the imported .3dp: ";
      cin >> filepath;
      if (filepath != "") {
        world = import3dp(filepath);
        cursor = world->getCursor();
      }
      break;
  }
  glutPostRedisplay();
}

/*
 * Special key input handler -- called by glutSpecialFunc.
 */
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
