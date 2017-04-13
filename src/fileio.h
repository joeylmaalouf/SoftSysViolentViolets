#ifndef FILEIO_H
#define FILEIO_H

#include "util.h"
#include "world.h"

vector<vector<float>> getCorners (float x, float y, float z, float s);
vector<vector<vector<float>>> getTriangles (vector<vector<float>> corners);
string buildFacetString (int n, vector<vector<float>> triangle);
void exportStl (World *world, string filepath);
void importStl (string filepath);

#endif /* FILEIO_H */
