#include "util.h"

class Voxel {
  private:
    tuple3i pos;
    tuple3i col;

  public:
    Voxel (tuple3i p, tuple3i c) {
      pos = p;
      col = c;
    }

    tuple3i getPosition () {
      return pos;
    };

    tuple3i getColor () {
      return col;
    };
};
