#include <iostream>

int main() {
  constexpr double gravity{9.8};

  // 编译时分支预测完成常量
  if constexpr (gravity == 9.8) // now using constexpr if
    std::cout << "Gravity is normal.\n";
  else
    std::cout << "We are not on Earth.\n";

  return 0;
}