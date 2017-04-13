#ifndef VOXEL_H
#define VOXEL_H

#include "util.h"

class Voxel {
  private:
    vector<int> pos;
    vector<int> col;

  public:
    Voxel (vector<int> p, vector<int> c);
    vector<int> getPosition ();
    vector<int> getColor ();
};

#endif /* VOXEL_H */
