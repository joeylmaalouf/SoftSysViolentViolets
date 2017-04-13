#ifndef CURSOR_H
#define CURSOR_H

#include "util.h"
#include "voxel.h"

class Cursor {
  private:
    int shape;
    vector<int> color;
    vector<int> position;

  public:
    Cursor ();
    int getShape ();
    vector<int> getColor ();
    vector<int> getPosition ();
    void setShape (int flag);
    void setColor (vector<int> newColor);
    void move (vector<int> delta);
    void place (Voxel **voxels);
    void erase (vector<int> *positions);
};

#endif /* CURSOR_H */
