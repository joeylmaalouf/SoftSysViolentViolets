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
    map<tuple3i, Voxel> grid;
    Cursor cursor;
    tuple3i backgroundColor;

  public:
    World (Cursor c, tuple3i color);
    void handleInput (int event);
    void moveCursor (tuple3i position);
    void setCursorColor (tuple3i color);
    void setCursorShape (tuple3i shape);
    void placeVoxel ();
    void eraseVoxel ();
    void setBackgroundColor (tuple3i color);
};

#endif /* WORLD_H */
