#include "stack.h"

template <typename T> T Stack<T>::pop () {
  T back = elements.back();
  elements.pop_back();
  return back;
}

template <typename T> void Stack<T>::push (T element) {
  elements.push_back(element);
}

template <typename T> bool Stack<T>::empty () {
  return elements.empty();
}

template class Stack<Diff *>;  // http://stackoverflow.com/a/8752879
