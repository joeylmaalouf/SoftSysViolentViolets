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

void World::setCursorSize (int size) {
  cursor->setSize(size);
}

void World::placeVoxels () {
  vector<vector<int>> coords = cursor->getCoords();
  for (vector<int> pos : coords) {
    Voxel *vox = new Voxel(pos, cursor->getColor());
    grid[vox->getPosition()] = vox;
  }
}

void World::eraseVoxels () {
  vector<vector<int>> coords = cursor->getCoords();
  for (vector<int> pos : coords) {
    grid.erase(pos);
  }
}

void World::setBackgroundColor (vector<int> color) {
  backgroundColor = color;
}
