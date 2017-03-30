#include "voxel.h"

Voxel::Voxel (tuple3i p, tuple3i c) {
  pos = p;
  col = c;
}

tuple3i Voxel::getPosition () {
  return pos;
}

tuple3i Voxel::getColor () {
  return col;
}
