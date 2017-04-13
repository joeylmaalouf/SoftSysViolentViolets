#ifndef WORLD_H
#define WORLD_H

#include <map>
#include "cursor.h"
#include "util.h"
#include "voxel.h"

/*
 * Class representing the world of the drawing
 */
class World {
  private:
    map<vector<int>, Voxel *> grid;
    Cursor *cursor;
    vector<int> backgroundColor;

  public:
    World (map<vector<int>, Voxel *> g, Cursor *c, vector<int> color);
    map<vector<int>, Voxel *> getGrid ();
    void moveCursor (vector<int> position);
    Cursor *getCursor ();
    void setCursorColor (vector<int> color);
    void setCursorShape (int shape);
    void placeVoxel ();
    void eraseVoxel ();
    void setBackgroundColor (vector<int> color);
};

#endif /* WORLD_H */
