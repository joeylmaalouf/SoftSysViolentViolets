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

vector<vector<vector<float>>> getTrianglesAndNormal (vector<vector<float>> corners) {
  return {
    {corners[0], corners[1], corners[2], {-1.0,  0.0,  0.0}},
    {corners[2], corners[1], corners[3], {-1.0,  0.0,  0.0}},
    {corners[1], corners[0], corners[4], { 0.0, -1.0,  0.0}},
    {corners[1], corners[4], corners[5], { 0.0, -1.0,  0.0}},
    {corners[0], corners[2], corners[4], { 0.0,  0.0, -1.0}},
    {corners[4], corners[2], corners[6], { 0.0,  0.0, -1.0}},
    {corners[2], corners[3], corners[6], { 0.0,  1.0,  0.0}},
    {corners[6], corners[3], corners[7], { 0.0,  1.0,  0.0}},
    {corners[5], corners[4], corners[6], { 1.0,  0.0,  0.0}},
    {corners[5], corners[6], corners[7], { 1.0,  0.0,  0.0}},
    {corners[3], corners[1], corners[5], { 0.0,  0.0,  1.0}},
    {corners[3], corners[5], corners[7], { 0.0,  0.0,  1.0}}
  };
}

string buildFacetString (vector<vector<float>> triangle) {
  stringstream s;
  vector<float> normal = triangle[3];
  s << "  facet normal " << normal[0] << "E+0 " << normal[1] << "E+0 " << normal[2] << "E+0" << endl;
  s << "    outer loop" << endl;
  for (int i = 0; i < 3; i++) {
    vector<float> point = triangle[i];
    s << "      vertex " << point[0] << "E+0 " << point[1] << "E+0 " << point[2] << "E+0" << endl;
  }
  s << "    endloop" << endl;
  s << "  endfacet" << endl;
  return s.str();
}

void exportStl (World *world, string filepath) {
  ofstream fs;
  fs.open(filepath + ".stl");
  if (!fs.is_open()) {
    cout << "Error: could not open file '" << filepath << ".stl'." << endl;
    return;
  }

  fs << "solid " << filepath << endl;

  map<vector<int>, Voxel *> grid = world->getGrid();
  for (const auto &pair : grid) {
    int size = 1;
    float x = static_cast<float>(pair.first[0]);
    float y = static_cast<float>(pair.first[1]);
    float z = static_cast<float>(pair.first[2]);
    float s = size / 2.0;

    vector<vector<float>> corners = getCorners(x, y, z, s);
    vector<vector<vector<float>>> triangles = getTrianglesAndNormal(corners);
    for (vector<vector<float>> t : triangles) {
      fs << buildFacetString(t);
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
    fs << col[0] << " " << col[1] <<  " " << col[2] << endl;
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
