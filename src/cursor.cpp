#include "util.h"
#include "voxel.cpp"

class Cursor {
  private:
    tuple3i position;
    tuple3i color;
    int shape;

  public:
    int getShape () {
      return shape;
    }

    tuple3i getColor () {
      return color;
    }

    tuple3i getPosition () {
      return position;
    }

    void setShape (int flag) {
      shape = flag;
    }

    void setColor (tuple3i newColor) {
      color = newColor;
    }

    void move (tuple3i delta) {
      get<0>(position) = get<0>(position) + get<0>(delta);
      get<1>(position) = get<1>(position) + get<1>(delta);
      get<2>(position) = get<2>(position) + get<2>(delta);
    }

    void place (Voxel *voxels) {
      voxels[0] = Voxel(position, color);
    }

    void erase (tuple3i *positions) {
      positions[0] = position;
    }
};
