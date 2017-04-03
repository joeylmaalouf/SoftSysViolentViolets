#include "world.h"

World::World (Cursor c, tuple3i color) {
  grid = g;
  cursor = c;
  backgroundColor = color;
}

void World::moveCursor (tuple3i position) {
  cursor.move(position)
}

void World::setCursorColor (tuple3i color) {
  cursor.setColor(color)
}

void World::setCursorShape (int shape) {
  cursor.setShape(shape);
}

void World::placeVoxel () {
  Voxel *voxels;
  cursor.place(voxels);
  int num_voxels = sizeof(voxels);
  for (int i = 0; i < num_voxels; i++) {
    Voxel vox = voxels[i];
    grid[vox.getPosition()] = vox;
  }
}

void World::eraseVoxel () {
  tuple3i *positions;
  cursor.erase(positions);
  int num_positions = sizeof(positions);
  for (int i = 0; i < num_positions; i++) {
    grid.erase(positions[i]);
  }
}

void World::setBackgroundColor (tuple3i color) {
  backgroundColor = color;
}
