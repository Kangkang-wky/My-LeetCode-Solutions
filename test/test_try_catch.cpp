#include <fstream>
#include <iostream>

/*

noexcept 关键字 可以用 noexcept 标记函数，指出它不抛出任何异常：

void printVal(const vector<int>& values) noexcept;

如果一个函数带有 noexcept 标记，却以某种方式抛出了异常，C++ 将调用 terminate()
来终止程序运行。

*/

int main() {
  // try 可能抛出异常的代码块
  try {
    std::ifstream file("file.txt");
    if (!file.is_open()) {
      // throw 抛出异常块
      throw std::runtime_error("Failed to open file.");
    }
    // Do something with the file...
    file.close();
  }
  //
  catch (const std::exception &ex) {
    std::cerr << "Exception: " << ex.what() << std::endl;
  }
  return 0;
}
