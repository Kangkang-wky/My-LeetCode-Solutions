#include <iostream>

class MyClass {
public:
  void memberFunction(int value) {
    std::cout << "Member function called with value: " << value << std::endl;
  }
};

template <typename T>
void templateFunction(void (T::*func)(int), T *obj, int value) {
  (obj->*func)(value);
}

int main() {
  MyClass obj;
  templateFunction(&MyClass::memberFunction, &obj, 42);
  return 0;
}