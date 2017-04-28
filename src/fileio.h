#ifndef FILEIO_H
#define FILEIO_H

#include "util.h"
#include "world.h"

vector<vector<float>> getCorners (float x, float y, float z, float s);
vector<vector<vector<float>>> getTrianglesAndNormals (vector<vector<float>> corners);
string buildFacetString (vector<vector<float>> triangle);
void exportStl (World *world, string filepath);
void export3dp (World *world, string filepath);
World *import3dp (string filepath);

#endif /* FILEIO_H */
