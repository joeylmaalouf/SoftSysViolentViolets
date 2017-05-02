#ifndef CURSOR_H
#define CURSOR_H

#include "util.h"
#include "voxel.h"

/*
 * Represents the cursor used for adding to and removing from the world.
 */
class Cursor {
  private:
    int shape = 1;
    int size = 1; // size of the cursor
    vector<int> color = {0, 96, 0}; // color of the cursor, <r,g,b>
    vector<int> position = {0, 0, 0}; // position of the cursor, <x,y,z>

  public:
    /*
     * Getter and setter for cursor size.
     * Size is represented by an integer.
     */
    int getSize ();
    void setSize (int newSize);

    /*
     * Getter and setter for cursor shape.
     * Shape is represented by an integer:
     * 0 is spherical
     * 1 is cubic
     */
    int getShape ();
    void setShape (int shape_num);

    /*
     * Getter and setter for cursor color.
     * Color is represented by an <r,g,b> vector.
     */
    vector<int> getColor ();
    void setColor (vector<int> newColor);

    /*
     * Gets the position of the cursor.
     * return: a position vector, <x,y,z>
     */
    vector<int> getPosition ();

    /*
     * Moves the cursor relative to its current position.
     * delta: a vector <dx,dy,dz> which is added to current position
     */
    void move (vector<int> delta);

    /*
     * Gets the coordinates of all voxels in the cursor.
     * return: a vector of <x,y,z> position vectors
     */
    vector<vector<int>> getCoords ();
};

#endif /* CURSOR_H */
