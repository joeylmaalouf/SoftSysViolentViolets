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
    void display ();
    void rotateX ();
    void rotateY ();
    void rotateZ ();
    void reset ();
};
