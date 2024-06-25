#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

class string {
public:
  // 构造函数
  string(const char *str = "") : _str(new char[strlen(str) + 1]) {
    strcpy(_str, str);
  }

  // 析构函数
  ~string() {
    delete[] _str;
    _str = nullptr;
  }

  // 拷贝构造函数
  string(const string &s) : _str(nullptr) {
    string tmp(s._str);
    std::swap(_str, tmp._str);
  }

  // 赋值运算符重载
  // Modern C++ 采用 临时对象, swap 机制即可
  string &operator=(const string s) {
    string tmp(s._str);
    std::swap(_str, tmp._str);

    return *this;
  }

private:
  char *_str;
};
