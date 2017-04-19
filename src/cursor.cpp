#include "cursor.h"

Cursor::Cursor () {
  shape = 1;
  color = {0, 96, 0};
  position = {0, 0, 0};
}

int Cursor::getShape () {
  return shape;
}

vector<int> Cursor::getColor () {
  return color;
}

vector<int> Cursor::getPosition () {
  return position;
}

void Cursor::setShape (int flag) {
  shape = max(flag, 1);
}

void Cursor::setColor (vector<int> newColor) {
  color = newColor;
}

void Cursor::move (vector<int> delta) {
  position[0] += delta[0];
  position[1] += delta[1];
  position[2] += delta[2];
}

void Cursor::place (Voxel **voxels) {
  vector<int> this_pos = {0, 0, 0};
  int w = (2*shape) - 1;
  for (int x = -1*(shape - 1); x < shape; x++) {
    this_pos[0] = position[0] + x;
    for (int y = -1*(shape - 1); y < shape; y++) {
      this_pos[1] = position[1] + y;
      for (int z = -1*(shape - 1); z < shape; z++) {
        this_pos[2] = position[2] + z;
        Voxel *vox = new Voxel(this_pos, color);
        voxels[z + (w*y) + (w*w*x)] = vox;
      }
    }
  }
}

void Cursor::erase (vector<int> *positions) {
  vector<int> this_pos = {0, 0, 0};
  int w = (2*shape) - 1;
  for (int x = -1*(shape - 1); x < shape; x++) {
    this_pos[0] = position[0] + x;
    for (int y = -1*(shape - 1); y < shape; y++) {
      this_pos[1] = position[1] + y;
      for (int z = -1*(shape - 1); z < shape; z++) {
        this_pos[2] = position[2] + z;
        positions[z + (w*y) + (w*w*x)] = this_pos;
      }
    }
  }
}
