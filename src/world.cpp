#include "world.h"

World::World (map<vector<int>, Voxel *> g, Cursor *c, vector<int> color) {
  grid = g;
  cursor = c;
  backgroundColor = color;
}

map<vector<int>, Voxel *> World::getGrid() {
  return grid;
}

Cursor *World::getCursor () {
  return cursor;
}

void World::moveCursor (vector<int> position) {
  cursor->move(position);
}

void World::setCursorColor (vector<int> color) {
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
  vector<int> *positions = new vector<int>[num_positions];
  cursor->erase(positions);
  for (int i = 0; i < num_positions; i++) {
    grid.erase(positions[i]);
  }
}

void World::setBackgroundColor (vector<int> color) {
  backgroundColor = color;
}
