#include "cursor.h"

int Cursor::getSize () {
  return size;
}

int Cursor::getShape () {
  return shape;
}

vector<int> Cursor::getColor () {
  return color;
}

vector<int> Cursor::getPosition () {
  return position;
}

vector<vector<int>> Cursor::getCoords () {
  vector<vector<int>> list;
  vector<int> current = {0, 0, 0};
  long dist2;
  for (int x = -1 * (size - 1); x < size; x++) {
    current[0] = position[0] + x;
    for (int y = -1 * (size - 1); y < size; y++) {
      current[1] = position[1] + y;
      for (int z = -1 * (size - 1); z < size; z++) {
        current[2] = position[2] + z;
        if (shape == 0){
          dist2 = (x*x) + (y*y) + (z*z);
          if (dist2 <= (size*size)){
            list.push_back(current);
          }
        } else {
          list.push_back(current);
        }
      }
    }
  }
  return list;
}

void Cursor::setSize (int newSize) {
  size = max(newSize, 1);
}

void Cursor::setShape (int shape_num) {
  if ((shape_num >= 0) && (shape_num <= 1)) {
    shape = shape_num;
  }
}

void Cursor::setColor (vector<int> newColor) {
  color = newColor;
}

void Cursor::move (vector<int> delta) {
  position[0] += delta[0];
  position[1] += delta[1];
  position[2] += delta[2];
}
