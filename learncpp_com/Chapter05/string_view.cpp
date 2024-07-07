#include <iostream>
#include <string>
#include <string_view>

void printSV(std::string_view str) { std::cout << str << '\n'; }

int main() {
  // string_view 类型的使用

  printSV("Hello, world!"); // call with C-style string literal

  std::string s2{"Hello, world!"};
  printSV(s2); // call with std::string

  std::string_view s3{s2};
  printSV(s3); // call with std::string_view

  return 0;
}