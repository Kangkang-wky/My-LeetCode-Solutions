## 11.6 — 函数模板

### 命名模板参数

就像我们经常在平凡的情况下使用单个字母来表示变量名（例如x），当模板参数以平凡或明显的方式使用时，习惯上也使用单个大写字母（以 开头T）。例如，在我们的max函数模板中：

```c++
template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}
```

我们不需要给出T一个复杂的名称，因为它显然只是被比较的值的占位符类型，并且T可以是任何可以比较的类型（例如int、double或char，但不是nullptr）。

我们的函数模板一般都会使用这种命名约定。

如果类型模板参数具有不明显的用法或必须满足的特定要求，则此类名称有两种常见的约定：

以大写字母开头（例如Allocator）。标准库使用此命名约定。
以 为前缀T，然后以大写字母开头（例如TAllocator）。这使得更容易看出该类型是类型模板参数。
选择哪一个取决于个人喜好。


```c++
template< class T, class Compare >
const T& max( const T& a, const T& b, Compare comp ); // ignore the & for now, we'll cover these in a future lesson
```

## 11.10 — 在多个文件中使用函数模板

### 

max.h

```c++
#ifndef MAX_H
#define MAX_H

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

#endif
```


foo.cpp

```c++
#include "max.h" // import template definition for max<T>(T, T)
#include <iostream>

void foo()
{
	std::cout << max(3, 2) << '\n';
}
```

main.cpp

```c++
#include "max.h" // import template definition for max<T>(T, T)
#include <iostream>

void foo(); // forward declaration for function foo

int main()
{
    std::cout << max(3, 5) << '\n';
    foo();

    return 0;
}
```

### 最佳实践

多个文件中需要的模板应该在头文件中定义，然后在需要的地方使用 #included。这样编译器就可以查看完整的模板定义，并在需要时实例化模板。