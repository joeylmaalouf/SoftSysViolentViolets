#ifndef DIFF_H
#define DIFF_H

#include "voxel.h"

class Diff {
  private:

  public:
    int num_added;
    Voxel **added;
    int num_removed;
    Voxel **removed;

    Diff (int na, Voxel **a, int nr, Voxel **r);
};

#endif /* DIFF_H */
