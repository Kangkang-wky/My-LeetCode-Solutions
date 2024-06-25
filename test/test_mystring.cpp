#include <cstdio>
#include <cstdlib>
#include <cstring>

class MyString {
private:
  char *_data;
  size_t _len;
  void _init_data(const char *s) {
    _data = new char[_len + 1];
    memcpy(_data, s, _len);
    _data[_len] = '\0';
  }

public:
  // 构造函数
  MyString() {
    _data = nullptr;
    _len = 0;
  }
  // 构造函数
  MyString(const char *p) {
    _len = strlen(p);
    _init_data(p);
  }
  // 拷贝构造函数
  MyString(const MyString &str) {
    _len = str._len;
    _init_data(str._data);
  }
  // 移动构造函数
  MyString(MyString &&str) noexcept {
    _len = str._len;
    _data = str._data;
    str._len = 0;
    str._data = NULL;
  }
  // 赋值运算符重载
  MyString &operator=(const MyString &str) {
    if (this != &str) {
      _len = str._len;
      _init_data(str._data);
    }
    return *this;
  }
  // 移动赋值运算符重载
  MyString &operator=(MyString &&str) noexcept {
    if (this != &str) {
      _len = str._len;
      _data = str._data;
      str._len = 0;
      str._data = NULL;
    }
    return *this;
  }
  virtual ~MyString() {
    if (_data)
      delete _data;
  }
};
// 返回值优化的函数
// Return value optimization
MyString create_string() {
  MyString str("Hello, World!"); // 临时对象
  return str; // 返回值优化（RVO/NRVO）可以避免这里的拷贝
}
int main() {
  MyString s = create_string();
  return 0;
}