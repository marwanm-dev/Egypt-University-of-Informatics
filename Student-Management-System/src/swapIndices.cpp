// Swaps the target element with the last index
template <class T> void swapIndices(T &a, T &b) {
  T temp = a;
  a = b;
  b = temp;
}
