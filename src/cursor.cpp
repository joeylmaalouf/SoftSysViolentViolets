#include "cursor.h"

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
  shape = flag;
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
  voxels[0] = Voxel(position, color);
}

void Cursor::erase (tuple3i *positions) {
  positions[0] = position;
}
