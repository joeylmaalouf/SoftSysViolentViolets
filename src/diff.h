#ifndef DIFF_H
#define DIFF_H

#include "voxel.h"

/*
 * Represents the difference between two world states.
 */
class Diff {
  private:

  public:
    int num_added; // number of blocks the diff added to the world
    Voxel **added; // list of blocks the diff added to the world
    int num_removed; // number of blocks the diff removed from the world
    Voxel **removed; // list of blocks the diff removed from the world

    /*
     * Constructor for Diff.
     * na: sets num_added
     * a: sets added
     * nr: sets num_removed
     * r: sets removed
     */
    Diff (int na, Voxel **a, int nr, Voxel **r);
};

#endif /* DIFF_H */
