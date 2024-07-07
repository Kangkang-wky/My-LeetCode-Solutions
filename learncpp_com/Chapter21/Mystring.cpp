#include <algorithm> // for std::max and std::copy_n
#include <iostream>

class MyString {
private:
  // 两个成员变量
  char *m_data{};
  int m_length{};

public:
  // 构造函数
  MyString(const char *data = nullptr, int length = 0)
      : m_length{std::max(length, 0)} {
    if (length) {
      m_data = new char[static_cast<std::size_t>(length)];
      std::copy_n(data, length,
                  m_data); // copy length elements of data into m_data
    }
    std::cerr << "Constructor function" << std::endl;
  }

  // 拷贝构造函数
  MyString(const MyString &source);

  // 移动构造函数
  MyString(MyString &&arr);

  ~MyString() {
    m_length = 0;
    delete[] m_data;
  }

  // Overloaded assignment
  MyString &operator=(const MyString &str) noexcept;

  // 移动赋值函数
  MyString &operator=(MyString &&arr) noexcept;

  // 友元函数, 访问私有数据成员
  friend std::ostream &operator<<(std::ostream &out, const MyString &s);

  // get string
  char *getString();
  // get length
  int getLength();
};

char *MyString::getString() { return m_data; }

int MyString::getLength() { return m_length; }

std::ostream &operator<<(std::ostream &out, const MyString &s) {
  out << s.m_data;
  return out;
}

// 拷贝构造函数

MyString::MyString(const MyString &str) {

  // first we need to deallocate any value that this string is holding!
  if (m_data) {
    delete[] m_data;
  }

  // because m_length is not a pointer, we can shallow copy it
  m_length = str.m_length;

  // m_data is a pointer, so we need to deep copy it if it is non-null
  if (m_length) {

    m_data = new char[static_cast<std::size_t>(str.m_length)];
    std::copy_n(str.m_data, m_length, m_data);

  } else {
    m_data = nullptr;
  }

  std::cerr << "Copy Constructor function" << std::endl;
}

// 拷贝赋值函数
MyString &MyString::operator=(const MyString &str) noexcept {
  // self-assignment check,
  if (this == &str) {
    std::cerr << "copy assignment operator" << std::endl;
    return *this;
  }

  // if data exists in the current string, delete it
  if (m_data) {
    delete[] m_data;
  }

  m_length = str.m_length;

  // allocate a new array of the appropriate length
  if (m_length) {
    m_data = new char[static_cast<std::size_t>(str.m_length)];
    std::copy_n(str.m_data, m_length,
                m_data); // copies m_length elements of str.m_data into m_data
  } else {
    m_data = nullptr;
  }

  std::cerr << "copy assignment operator" << std::endl;

  // return the existing object so we can chain this operator
  return *this;
}

// Move constructor
MyString::MyString(MyString &&arr)
    : m_data(arr.m_data), m_length(arr.m_length) {
  arr.m_length = 0;
  arr.m_data = nullptr;

  std::cerr << "Move Constructor function" << std::endl;
}

// Move assignment
MyString &MyString::operator=(MyString &&arr) noexcept {
  // self-assignment check
  if (&arr == this) {
    std::cerr << "move assignment operator" << std::endl;
    return *this;
  }

  delete[] m_data;

  m_length = arr.m_length;
  m_data = arr.m_data;
  arr.m_length = 0;
  arr.m_data = nullptr;

  std::cerr << "move assignment operator" << std::endl;

  return *this;
}

int main() {
  MyString alex("Alex", 5); // Constructor function
  MyString employee1;       // Constructor function
  employee1 = alex;         // copy assignment operator

  MyString employee2 = alex; // Copy Constructor function

  MyString employee3(alex); // Copy Constructor function

  MyString employee4(std::move(alex)); // Move Constructor function

  MyString employee5; // Constructor function

  employee5 = std::move(alex); // move assignment operator

  return 0;
}