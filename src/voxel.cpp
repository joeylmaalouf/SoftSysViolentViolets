#include "util.h"

class Voxel {
  private:
    tuple3i pos;
    tuple3i color;

    Voxel (tuple3i p, tuple3i c) {
      pos = p;
      color = c;
    }

    tuple3i getColor () {
      return color;
    };
};
