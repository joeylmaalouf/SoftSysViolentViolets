#ifndef CAMERA_H
#define CAMERA_H

#include "cursor.h"
#include "util.h"
#include "world.h"

/*
 * Draws a cube.
 * pos: a vector specifying the center of the cube, <x,y,z>
 * color: a vector specifying the color of the cube, <r,g,b>
 * size: the side length of the cube
 * draw_flag: if GL_LINES, cube will be wireframe; otherwise, cube will be solid
 */
void drawCube (vector<int> pos, vector<int> col, int draw_flag);

/*
 * Represents a camera.
 */
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
    double eyeX = 3;
    double eyeY = 2;
    double eyeZ = 5;

    // ...position of reference point
    double centerX = 0;
    double centerY = 0;
    double centerZ = 0;

    // ...direction of up vector
    double upX = 0;
    double upY = 1;
    double upZ = 0;

    // for glRotate
    // (https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glRotate.xml)
    double rotationX = 0;
    double rotationY = 0;
    double rotationZ = 0;

  public:
    /*
     * Displays the world.
     * world: a pointer to the world to display
     */
    void display (World *world);

    /*
     * Sets camera rotation around each axis.
     * degrees: the number of degrees to rotate the camera, counterclockwise
     */
    void rotateX (int degrees);
    void rotateY (int degrees);
    void rotateZ (int degrees);

    /*
     * Resets camera rotation.
     */
    void reset ();

    /*
     * Sets camera zoom.
     * scalar: the zoom multiplier. scalar > 1 zooms out; scalar < 1 zooms in.
     */
    void zoom (double scalar);
};

#endif /* CAMERA_H */
