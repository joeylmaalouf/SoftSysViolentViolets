#include "util.h"

class Voxel {
  private:
    tuple3i pos;
    tuple3i col;

  public:
    Voxel (tuple3i p, tuple3i c);
    tuple3i getPosition ();
    tuple3i getColor ();
};
