#include <GL/glut.h>

class Camera {
  private:
    // for gluPerspective:
    // (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluPerspective.xml)
    double fovy = 60; // field of view angle, in degrees, in the y direction
    double aspect; // aspect ratio -- x (width) / y (height). determines field of view in x direction.
    double zNear = 0.1; // distance from viewer to near clipping plane. MUST be positive.
    double zFar = 100; // distance from viewer to far clipping plane. MUST be positive.

    // for gluLookAt
    // (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/gluLookAt.xml)
    // ...position of eye point
    double eyeX = 5;
    double eyeY = 5;
    double eyeZ = 5;

    // ...position of reference point
    double centerX = 0;
    double centerY = 0;
    double centerZ = 0;

    // ...direction of up vector
    double upX = 0;
    double upY = 0;
    double upZ = 1;

    // for glRotate
    // (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glRotate.xml)
    double rotateX = 0;
    double rotateY = 0;
    double rotateZ = 0;

  public:
    Camera() {
      int w = glutGet(GLUT_WINDOW_WIDTH);
      int h = glutGet(GLUT_WINDOW_HEIGHT);
      Camera::aspect = w / h;
      gluPerspective(fovy, aspect, zNear, zFar);

      gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);

      gluRotated(rotateX, 1.0, 0.0, 0.0);
      gluRotated(rotateY, 0.0, 1.0, 0.0);
      gluRotated(rotateZ, 0.0, 0.0, 1.0);
    }
};
