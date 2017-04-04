#ifndef CURSOR_H
#define CURSOR_H

#include "util.h"
#include "voxel.h"

class Cursor {
  private:
    int shape;
    tuple3i color;
    tuple3i position;

  public:
    Cursor ();
    int getShape ();
    tuple3i getColor ();
    tuple3i getPosition ();
    void setShape (int flag);
    void setColor (tuple3i newColor);
    void move (tuple3i delta);
    void place (Voxel **voxels);
    void erase (tuple3i *positions);
};

#endif /* CURSOR_H */
