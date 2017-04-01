#include "world.h"

World::World (map<tuple3i, Voxel> g, Cursor c, tuple3i color) {
  grid = g;
  cursor = c;
  backgroundColor = color;
}

void World::handleInput (int event) {
  // TODO: event needs to be better defined before
  //       actually finishing this implementation
  switch (event) {
    case 0:
      // cursor.move(pos);
      break;
    case 1:
      // cursor.setColor(color);
      break;
    case 2:
      // cursor.setShape(flag);
      break;
    case 3:
      Voxel *voxels;
      cursor.place(voxels);
      int w = (2 * cursor.getShape()) - 1;
      for (int i = 0; i < (w*w*w); i++) {
        Voxel vox = voxels[i];
        grid[vox.getPosition()] = vox;
      }
      break;
    case 4:
      tuple3i *positions;
      cursor.erase(positions);
      int w = (2 * cursor.getShape()) - 1;
      for (int i = 0; i < (w*w*w); i++) {
        grid.erase(positions[i]);
      }
      break;
    default:
      break;
  }
}

void World::setBackgroundColor (tuple3i color) {
  backgroundColor = color;
}
