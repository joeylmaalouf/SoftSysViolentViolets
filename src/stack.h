#ifndef STACK_H
#define STACK_H

#include <cstddef>
#include <vector>

#include "diff.h"

using namespace std;

/*
 * Represents a generic stack.
 */
template <typename T> // T is the generic type
class Stack {
  private:
    vector<T> elements;

  public:
    /*
     * Pops and returns the top element of the stack.
     */
    T pop ();

    /*
     * Pushes an element onto the stack.
     */
    void push (T element);

    /*
     * Returns true if the stack is empty and false otherwise.
     */
    bool empty ();
};

#endif /* STACK_H */
