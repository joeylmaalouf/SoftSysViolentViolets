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
    World (map<vector<int>, Voxel *> g, Cursor *c, vector<int> color);
    map<vector<int>, Voxel *> getGrid ();
    void moveCursor (vector<int> position);
    Cursor *getCursor ();
    void setCursorColor (vector<int> color);
    void setCursorSize (int size);
    void placeVoxels ();
    void eraseVoxels ();
    void setBackgroundColor (vector<int> color);
    void undo ();
    void redo ();
};

#endif /* WORLD_H */
