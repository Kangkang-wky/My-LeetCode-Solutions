#include <iostream>
#include <new> // For std::bad_alloc

int main() {
  try {
    int *ptr = new int[10000000000];
    // Do something with the allocated memory...
    delete[] ptr;
  } catch (const std::bad_alloc &ex) {
    std::cerr << "Exception: Failed to allocate memory." << std::endl;
  }
  return 0;
}
