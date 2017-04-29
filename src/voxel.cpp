#include "voxel.h"

Voxel::Voxel (vector<int> p, vector<int> c) {
  pos = p;
  color = c;
}

vector<int> Voxel::getPosition () {
  return pos;
}

vector<int> Voxel::getColor () {
  return color;
}
