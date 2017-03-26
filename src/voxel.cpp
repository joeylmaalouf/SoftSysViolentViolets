#include <tuple>

using namespace std;

#ifndef tuple3i
  #define tuple3i tuple<int, int, int>
#endif

class Voxel {
  private:
    tuple3i pos;
    tuple3i color;

    Voxel (tuple3i p, tuple3i c) {
      pos = p;
      color = c;
    }

    tuple3i getColor () {
      return color;
    };
};
