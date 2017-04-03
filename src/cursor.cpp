#include "cursor.h"

Cursor::Cursor () {
  shape = 1;
  color = make_tuple(127, 0, 0);
  position = make_tuple(0, 0, 0);
}

int Cursor::getShape () {
  return shape;
}

tuple3i Cursor::getColor () {
  return color;
}

tuple3i Cursor::getPosition () {
  return position;
}

void Cursor::setShape (int flag) {
  shape = max(flag, 1);
}

void Cursor::setColor (tuple3i newColor) {
  color = newColor;
}

void Cursor::move (tuple3i delta) {
  get<0>(position) = get<0>(position) + get<0>(delta);
  get<1>(position) = get<1>(position) + get<1>(delta);
  get<2>(position) = get<2>(position) + get<2>(delta);
}

void Cursor::place (Voxel *voxels) {
  tuple3i this_pos;
  int w = (2*shape) - 1;
  for (int x = -1*(shape - 1); x < shape; x++) {
    get<0>(this_pos) = get<0>(position) + x;
    for (int y = -1*(shape - 1); y < shape; y++) {
      get<1>(this_pos) = get<1>(position) + y;
      for (int z = -1*(shape - 1); z < shape; z++) {
        get<2>(this_pos) = get<2>(position) + z;
        voxels[z + (w*y) + (w*w*x)] = Voxel(this_pos, color);
      }
    }
  }
}

void Cursor::erase (tuple3i *positions) {
  tuple3i this_pos;
  int w = (2*shape) - 1;
  for (int x = -1*(shape - 1); x < shape; x++) {
    get<0>(this_pos) = get<0>(position) + x;
    for (int y = -1*(shape - 1); y < shape; y++) {
      get<1>(this_pos) = get<1>(position) + y;
      for (int z = -1*(shape - 1); z < shape; z++) {
        get<2>(this_pos) = get<2>(position) + z;
        positions[z + (w*y) + (w*w*x)] = this_pos;
      }
    }
  }
}
