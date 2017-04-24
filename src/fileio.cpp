#include <fstream>
#include <iostream>
#include <sstream>
#include "fileio.h"

vector<vector<float>> getCorners (float x, float y, float z, float s) {
  return {
    {x - s, y - s, z - s},
    {x - s, y - s, z + s},
    {x - s, y + s, z - s},
    {x - s, y + s, z + s},
    {x + s, y - s, z - s},
    {x + s, y - s, z + s},
    {x + s, y + s, z - s},
    {x + s, y + s, z + s}
  };
}

vector<vector<vector<float>>> getTriangles (vector<vector<float>> corners) {
  return {
    {corners[0], corners[1], corners[2]}, {corners[1], corners[2], corners[3]},
    {corners[0], corners[1], corners[4]}, {corners[1], corners[4], corners[5]},
    {corners[0], corners[2], corners[4]}, {corners[2], corners[4], corners[6]},
    {corners[2], corners[3], corners[6]}, {corners[3], corners[6], corners[7]},
    {corners[4], corners[5], corners[6]}, {corners[5], corners[6], corners[7]},
    {corners[1], corners[3], corners[5]}, {corners[3], corners[5], corners[7]}
  };
}

string buildFacetString (int n, vector<vector<float>> triangle) {
  stringstream s;
  s << "facet normal 0.0e1 0.0e1 " << n << ".0e1" << endl << "    outer loop" << endl;
  for (int i = 0; i < 3; i++) {
    vector<float> point = triangle[i];
    s << "        vertex " << point[0] << "e1 " << point[1] << "e1 " << point[2] << "e1" << endl;
  }
  s << "    endloop" << endl << "endfacet" << endl;
  return s.str();
}

void exportStl (World *world, string filepath) {
  ofstream fs;
  fs.open(filepath + ".stl");
  if (!fs.is_open()) {
    cout << "Error: could not open file '" << filepath << ".stl'." << endl;
    return;
  }

  // https://en.wikipedia.org/wiki/STL_(file_format)#ASCII_STL
  fs << "solid " << filepath << endl;

  map<vector<int>, Voxel *> grid = world->getGrid();
  int n = 0;
  for (const auto &pair : grid) {
    int size = 1;
    float x = static_cast<float>(pair.first[0]);
    float y = static_cast<float>(pair.first[1]);
    float z = static_cast<float>(pair.first[2]);
    float s = size / 2.0;

    vector<vector<float>> corners = getCorners(x, y, z, s);

    vector<vector<vector<float>>> triangles = getTriangles(corners);

    for (vector<vector<float>> t : triangles) {
      fs << buildFacetString(n, t);
      n++;
    }
  }

  fs << "endsolid " << filepath << endl;

  fs.close();
}

void export3dp (World *world, string filepath) {
  ofstream fs;
  fs.open(filepath + ".3dp");
  if (!fs.is_open()) {
    cout << "Error: could not open file '" << filepath << ".3dp'." << endl;
    return;
  }

  map<vector<int>, Voxel *> grid = world->getGrid();
  for (const auto &pair : grid) {
    vector<int> pos = pair.second->getPosition();
    vector<int> col = pair.second->getColor();
    fs << pos[0] << " " << pos[1] <<  " " << pos[2] <<  " ";
    fs << col[0] <<  " " << col[1] <<  " " << col[2] << endl;
  }

  fs.close();
}

World *import3dp (string filepath) {
  ifstream fs;
  fs.open(filepath + ".3dp");

  Cursor *cursor = new Cursor();
  map<vector<int>, Voxel *> grid;
  int x, y, z, r, g, b;

  while (fs >> x >> y >> z >> r >> g >> b) {
    grid[{x, y, z}] = new Voxel({x, y, z}, {r, g, b});
  }

  return new World(grid, cursor, {0, 0, 0});
}
