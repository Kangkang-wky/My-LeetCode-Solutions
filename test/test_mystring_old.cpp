#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

namespace Mystring {

class string {
private:
  const char *c_string_;

public:
  // Clones a 0-terminated C string, allocating memory using new.
  // 第一要义是检查传入的指针是否为空, 这是必须要提前确认的
  static const char *CloneCString(const char *a_c_string) {
    if (a_c_string == nullptr)
      return nullptr;

    const size_t len = strlen(a_c_string);
    char *const clone = new char[len + 1];
    memcpy(clone, a_c_string, len + 1);

    return clone;
  }

  void Set(const char *a_c_string) {

    // Makes sure this works when c_string == c_string_
    const char *const temp = CloneCString(a_c_string);
    delete[] c_string_;
    c_string_ = temp;
  }

  // 构造函数
  string() : c_string_(nullptr){};

  // 显示构造函数
  explicit string(const char *a_c_string) : c_string_(nullptr) {
    // 注意此处一定要有非空验证
    Set(a_c_string);
  }

  // 拷贝构造函数
  string(const string &s) {
    // 注意此处一定要有非空验证
    Set(s.c_string_);
  }

  // 移动构造函数
  string(string &&s) noexcept {
    delete[] c_string_;
    c_string_ = s.c_string_;
    s.c_string_ = nullptr;
  }

  // 析构函数
  ~string() { delete[] c_string_; }

  // 拷贝赋值运算符重载
  string &operator=(const string &s) {

    Set(s.c_string_);
    return *this;
  }

  // 移动赋值运算符重载
  string &operator=(string &&s) noexcept {
    delete[] c_string_;
    c_string_ = s.c_string_;
    s.c_string_ = nullptr;
    return *this;
  }
};

} // namespace Mystring
