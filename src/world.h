#ifndef WORLD_H
#define WORLD_H

#include "cursor.h"
#include "util.h"
#include "voxel.h"
#include "stack.h"
#include "diff.h"

class World {
  private:
    map<vector<int>, Voxel *> grid;
    Cursor *cursor;
    vector<int> backgroundColor;
    Stack<Diff *> undos; // diffs that can be undone (moves and redos)
    Stack<Diff *> redos; // diffs that can be redone (undos)

  public:
    /*
     * Constructor for World.
     * g: a map from <x,y,z> position to pointer to voxel; represents the initial grid
     * c: a pointer to the cursor
     * color: an <r,g,b>
     */
    World (map<vector<int>, Voxel *> g, Cursor *c, vector<int> color);

    /*
     * Getters for the cursor and the grid.
     */
    map<vector<int>, Voxel *> getGrid ();
    Cursor *getCursor ();

    /*
     * Setters for cursor color and size.
     */
    void setCursorColor (vector<int> color);
    void setCursorSize (int size);

    /*
     * Moves the cursor relative to its current position.
     * delta: a vector <dx,dy,dz> which is added to current position
     */
    void moveCursor (vector<int> delta);

    /*
     * Places voxels in the world in the shape, position, and color of the cursor.
     */
    void placeVoxels ();

    /*
     * Erases voxels from the world in the shape and position of the cursor.
     */
    void eraseVoxels ();

    /*
     * Sets the background color of the world.
     * color: an <r,g,b> vector
     */
    void setBackgroundColor (vector<int> color);

    /*
     * Undoes the last move or redo.
     */
    void undo ();

    /*
     * Redoes the last undo.
     */
    void redo ();
};

#endif /* WORLD_H */
