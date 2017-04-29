#ifndef VOXEL_H
#define VOXEL_H

#include "util.h"

/*
 * Represents a unit of volume in the world.
 */
class Voxel {
  private:
    vector<int> pos;
    vector<int> color;

  public:
    /*
     * Constructor for Voxel.
     * p: an <x,y,z> vector representing the position of the center of the voxel
     * c: an <r,g,b> vector representing the color of the voxel
     */
    Voxel (vector<int> p, vector<int> c);

    /*
     * Getters for position and color
     */
    vector<int> getPosition ();
    vector<int> getColor ();
};

#endif /* VOXEL_H */
