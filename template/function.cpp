#include <functional>
#include <iostream>
#include <string>
#include <vector>

// function 实现对函数的封装
// Ret 返回值, Args 函数参数 构成函数签名
template <typename Ret, typename... Args> struct Function;

//
template <typename Ret, typename... Args> struct Function<Ret(Args...)> {
  // 通过父类指针指向子类 以及模板 来实现不同的类型
  // Base 基类, 两个纯虚函数
  struct Base {
    virtual Base *clone() = 0;

    virtual Ret operator()(Args &&...args) = 0;
  };

  // 子类Data 虚函数
  template <typename T> struct Data : Base {
    T func;
    Data(const T &t) : func(t) {}

    // 虚函数在拷贝构造时为 为函数对象去申请空间, 引入运行时开销
    virtual Base *clone() { return new Data<T>(func); }

    virtual Ret operator()(Args &&...args) {
      return func(std::forward<Args>(args)...);
    }
  };

  Base *ptr;

  // 实现 Function 一系列构造函数
  Function() : ptr{nullptr} {}

  template <typename T> Function(T t) : ptr{new Data<T>(t)} {};

  // 拷贝操作: 拷贝操作需要注意拷贝 函数对象
  Function(const Function &rhs) { ptr = rhs.ptr->clone(); }

  Function &operator=(const Function &rhs) {
    if (ptr)
      delete ptr;
    ptr = rhs.ptr->clone();
    return *this;
  }

  // 移动操作: 移动操作注意需要置空指针
  Function(Function &&rhs) noexcept {
    ptr = rhs.ptr;
    rhs.ptr = nullptr;
  }

  Function &operator=(Function &&rhs) noexcept {
    if (ptr)
      delete ptr;
    ptr = rhs.ptr;
    rhs.ptr = nullptr;
    return *this;
  }

  Ret operator()(Args... args) { return (*ptr)(std::forward<Args>(args)...); }

  // 析构
  ~Function() {
    if (ptr)
      delete ptr;
  }
};
void foo(int n, Function<void()> &call_back) {
  int sum = 0;
  for (int i = 1; i <= n; i++)
    sum += i;
  call_back = [=]() {
    std::cout << "sum  from 1"
              << " to " << n << " is " << sum << std::endl;
  };
}
int main() {
  srand(time(NULL));

  std::vector<Function<void()>> func(3);
  for (auto &f : func) {
    foo(rand(), f); // 回调函数
  }

  Function<int(int)> fib = [&](int n) {
    if (n == 0 || n == 1)
      return 1;
    return fib(n - 1) + fib(n - 2);
  };

  for (int i = 0; i < 10; i++)
    std::cout << fib(i) << " ";
  std::cout << std::endl;

  for (auto &f : func) {
    f(); // 发生函数调用
  }
}