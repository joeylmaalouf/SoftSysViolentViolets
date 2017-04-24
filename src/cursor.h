#ifndef CURSOR_H
#define CURSOR_H

#include "util.h"
#include "voxel.h"

class Cursor {
  private:
    int shape;
    int radius;
    vector<int> color;
    vector<int> position;

  public:
    Cursor ();
    int getSize ();
    int getShape ();
    vector<int> getColor ();
    vector<int> getPosition ();
    vector<vector<int>> getCoords ();
    void setSize (int size);
    void setShape (int shape_num);
    void setColor (vector<int> newColor);
    void move (vector<int> delta);
};

#endif /* CURSOR_H */
