#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <vector>

#include "diff.h"

using namespace std;

template <typename T>
class Stack {
  private:
    vector<T> elements;

  public:
    T pop ();
    void push (T element);
    bool empty ();
};

#endif /* STACK_H */
