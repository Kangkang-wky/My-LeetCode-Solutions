#include <iostream>
#include <string>

const std::string &getProgramName() // returns a const reference
{
  // 注意此处是 static 类型的
  // 如果是非 static 类型的变量, 随着这个函数结束, 其生命周期也会结束
  // 则按照 const 引用返回会发生错误
  static const std::string s_programName{
      "Calculator"}; // has static duration, destroyed at end of program

  return s_programName;
}

int main() {
  std::cout << "This program is named " << getProgramName();

  return 0;
}