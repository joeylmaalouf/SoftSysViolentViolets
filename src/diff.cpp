#include "diff.h"

Diff::Diff (int na, Voxel **a, int nr, Voxel **r) {
  num_added = na;
  added = a;
  num_removed = nr;
  removed = r;
}
