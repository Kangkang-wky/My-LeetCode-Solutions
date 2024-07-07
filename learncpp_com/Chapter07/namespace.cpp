#include <iostream>

// 命名空间与函数 function

namespace Foo // define a namespace named Foo
{
// This doSomething() belongs to namespace Foo
int doSomething(int x, int y) { return x + y; }
} // namespace Foo

namespace Goo // define a namespace named Goo
{
// This doSomething() belongs to namespace Goo
int doSomething(int x, int y) { return x - y; }
} // namespace Goo

int main() {
  std::cout << Foo::doSomething(4, 3)
            << '\n'; // use the doSomething() that exists in namespace Foo
  std::cout << Goo::doSomething(4, 3)
            << '\n'; // use the doSomething() that exists in namespace Goo
  return 0;
}