#ifndef FILEIO_H
#define FILEIO_H

#include "util.h"
#include "world.h"

void import_stl (string filepath);
void export_stl (World *world, string filepath);

#endif /* FILEIO_H */
