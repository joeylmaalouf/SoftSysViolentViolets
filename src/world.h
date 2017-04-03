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
    World (map<tuple3i, Voxel> g, Cursor c, tuple3i color);
    void handleInput (int event);
    void setBackgroundColor (tuple3i color);
};

#endif /* WORLD_H */
