#ifndef FILEIO_H
#define FILEIO_H

#include "util.h"
#include "world.h"

/*
 * Computes the corners of a cube.
 * x, y, z: the position coordinates for the cube
 * s: the side length of the cube
 * return: a vector of <x,y,z> position vectors
 */
vector<vector<float>> getCorners (float x, float y, float z, float s);

/*
 * Computes triangular face representations for a cube.
 * corners: a vector of the <x,y,z> corners of the cube.
 * return: a vector of <vertex1,vertex2,vertex3> triangle vertices, where
 *         each vertex is a <x,y,z> position vector.
 */
vector<vector<vector<float>>> getTriangles (vector<vector<float>> corners);

/*
 * Builds an STL string representing a facet.
 * n: an identifying number
 * triangle: a vector of <vertex1,vertex2,vertex3> triangle vertices, where
 *           each vertex is a <x,y,z> position vector.
 * return: an STL string
 */
string buildFacetString (int n, vector<vector<float>> triangle);

/*
 * Exports a world to STL.
 * world: a pointer to the world to export
 * filepath: the destination filepath for the exported STL
 */
void exportStl (World *world, string filepath);

/*
 * Exports a world in a custom format (designed to be easily importable).
 * world: a pointer to the world to export
 * filepath: the destination filepath for the exported 3dp file
 */
void export3dp (World *world, string filepath);

/*
 * Imports a world from custom format.
 * filepath: the source filepath for the 3dp file to import
 * return: a pointer to the imported world
 */
World *import3dp (string filepath);

#endif /* FILEIO_H */
