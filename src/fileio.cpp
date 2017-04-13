#include <fstream>
#include <iostream>
#include <vector>
#include "fileio.h"

void import_stl (string filepath) {
}

void export_stl (World *world, string filepath) {
  ofstream fs;
  fs.open(filepath + ".stl");
  if (!fs.is_open()) {
    cout << "Error: could not open file '" << filepath << ".stl'." << endl;
    return;
  }

  fs << "solid " << filepath << endl;

  map<tuple3i, Voxel *> grid = world->getGrid();
  int n = 0;
  for (const auto &g : grid) {
    int size = 1; // same as in drawCube, maybe make into an attribute of Voxel?
    float s = size / 2.0;
    float x = (float)get<0>(g.first);
    float y = (float)get<1>(g.first);
    float z = (float)get<2>(g.first);

    vector<vector<float>> corners = {
      {x - s, y - s, z - s},
      {x - s, y - s, z + s},
      {x - s, y + s, z - s},
      {x - s, y + s, z + s},
      {x + s, y - s, z - s},
      {x + s, y - s, z + s},
      {x + s, y + s, z - s},
      {x + s, y + s, z + s}
    };

    vector<vector<vector<float>>> triangles = {
      {corners[0], corners[1], corners[2]}, {corners[1], corners[2], corners[3]},
      {corners[0], corners[1], corners[4]}, {corners[1], corners[4], corners[5]},
      {corners[0], corners[2], corners[4]}, {corners[2], corners[4], corners[6]},
      {corners[2], corners[3], corners[6]}, {corners[3], corners[6], corners[7]},
      {corners[4], corners[5], corners[6]}, {corners[5], corners[6], corners[7]},
      {corners[1], corners[3], corners[5]}, {corners[3], corners[5], corners[7]}
    };

    for (vector<vector<float>> t : triangles) {
      fs << "facet normal 0.0e1 0.0e1 " << n << ".0e1" << endl << "    outer loop" << endl;
      for (int i = 0; i < 3; ++i) {
        vector<float> point = t[i];
        fs << "        vertex " << point[0] << "e1 " << point[1] << "e1 " << point[2] << "e1" << endl;
      }
      fs << "    endloop" << endl << "endfacet" << endl;
      ++n;
    }
  }

  fs << "endsolid " << filepath << endl;

  fs.close();
}
