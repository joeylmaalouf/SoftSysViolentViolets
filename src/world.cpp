#include "world.h"

World::World (map<vector<int>, Voxel *> g, Cursor *c, vector<float> color) {
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

void World::moveCursor (vector<int> delta) {
  cursor->move(delta);
}

void World::setCursorColor (vector<int> color) {
  cursor->setColor(color);
}

void World::setCursorSize (int size) {
  cursor->setSize(size);
}

void World::placeVoxels () {
  vector<vector<int>> coords = cursor->getCoords();
  map<vector<int>, Voxel *>::const_iterator it;
  int total_added = coords.size();
  int num_added = 0;
  Voxel **added = new Voxel*[total_added];
  int num_removed = 0;
  Voxel **removed = new Voxel*[total_added];  // total_added >= num_removed

  for (vector<int> pos : coords) {
    Voxel *add = new Voxel(pos, cursor->getColor());

    // check if the new placement will remove a voxel
    it = grid.find(pos);
    if (it != grid.end()) {
      removed[num_removed] = it->second;
      num_removed++;
    }

    // place the new voxel
    grid[pos] = add;
    added[num_added] = add;
    num_added++;
  }

  Diff *d = new Diff(num_added, added, num_removed, removed);
  undos.push(d);
}

void World::eraseVoxels () {
  vector<vector<int>> coords = cursor->getCoords();
  for (vector<int> pos : coords) {
    grid.erase(pos);
  }
}

void World::setBackgroundColor (vector<float> color) {
  backgroundColor = color;
}

void World::undo () {
  if (!undos.empty()) {
    Diff *d = undos.pop();

    // erase things the move-or-redo-being-undone added
    for (int i = 0; i < d->num_added; i++) {
      Voxel *a = d->added[i];
      grid.erase(a->getPosition());
    }

    // put back things the move-or-redo-being-undone removed
    for (int i = 0; i < d->num_removed; i++) {
      Voxel *r = d->removed[i];
      grid[r->getPosition()] = r;
    }

    redos.push(d);
  }
}

void World::redo () {
  if (!redos.empty()) {
    Diff *d = redos.pop();

    // erase things the undo-being-redone added
    for (int i = 0; i < d->num_removed; i++) {
      Voxel *r = d->removed[i];
      grid.erase(r->getPosition());
    }

    // put back things the undo-being-redone removed
    for (int i = 0; i < d->num_added; i++) {
      Voxel *a = d->added[i];
      grid[a->getPosition()] = a;
    }

    undos.push(d);
  }
}
