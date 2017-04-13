#include "world.h"

World::World (map<tuple3i, Voxel *> g, Cursor *c, tuple3i color) {
  grid = g;
  cursor = c;
  backgroundColor = color;
}

map<tuple3i, Voxel *> World::getGrid() {
  return grid;
}

Cursor *World::getCursor () {
  return cursor;
}

void World::moveCursor (tuple3i position) {
  cursor->move(position);
}

void World::setCursorColor (tuple3i color) {
  cursor->setColor(color);
}

void World::setCursorShape (int shape) {
  cursor->setShape(shape);
}

void World::placeVoxel () {
  int num_voxels = cursor->getShape();
  Voxel **voxels = new Voxel*[num_voxels];
  cursor->place(voxels);
  for (int i = 0; i < num_voxels; i++) {
    Voxel *vox = voxels[i];
    grid[vox->getPosition()] = vox;
  }
}

void World::eraseVoxel () {
  int num_positions = cursor->getShape();
  tuple3i *positions = new tuple3i[num_positions];
  cursor->erase(positions);
  for (int i = 0; i < num_positions; i++) {
    grid.erase(positions[i]);
  }
}

void World::setBackgroundColor (tuple3i color) {
  backgroundColor = color;
}
