#include "util.h"
#include "voxel.cpp"

class Cursor {
  private:
    tuple3i position;
    tuple3i color;
    int shape;

  public:
    void setShape (int flag) {
      shape = flag;
    }

    tuple3i getPosition () {
      return position;
    }

    tuple3i getColor () {
      return color;
    }

    int getShape () {
      return shape;
    }

    void setColor (tuple3i newColor) {
      get<0>(color) = get<0>(newColor);
      get<1>(color) = get<1>(newColor);
      get<2>(color) = get<2>(newColor);
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
