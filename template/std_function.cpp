#include <functional>
#include <iostream>

int add(int a, int b) { return a + b; }
int mul(int a, int b) { return a * b; }
int main() {
  std::function<int(int, int)> f1 = add;
  std::cout << f1(3, 5) << std::endl; // 8
  f1 = mul;
  std::cout << f1(3, 5) << std::endl; // 15
  std::function<void()> f2 = []() {
    std::cout << "hello function";
  }; // hello function
  f2();
}