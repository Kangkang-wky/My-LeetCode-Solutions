## 7.2 用户定义的命名空间和范围解析运算符

提醒一下，当两个相同的标识符被引入到同一作用域中，并且编译器无法消除使用哪一个的歧义时，就会发生命名冲突。发生这种情况时，编译器或链接器将产生错误，因为它们没有足够的信息来解决歧义。


## 7.3 局部变量

### 局部变量具有块作用域

局部变量具有块作用域，这意味着它们的范围从其定义点到其定义块的末尾。

变量的存储持续时间（通常简称为持续时间）决定了变量的创建（实例化）和销毁时间以及创建方式。在大多数情况下，变量的存储持续时间直接决定了它的持续lifetime时间。


### 局部变量没有链接

标识符还有另一个属性，名为linkage。标识符的linkage决定了同一标识符在不同作用域中的声明是否指向同一个对象（或函数）。

局部变量没有链接。每个没有链接的标识符声明都指向一个唯一的对象或函数。



## 7.4 全局变量

在 C++ 中，变量也可以在函数外部声明。这样的变量称为全局变量。

### 全局变量的作用域

在全局命名空间中声明的标识符具有**全局命名空间作用域**（通常称为**全局作用域**，有时非正式地称为文件作用域），这意味着它们从声明点到声明它们的文件结束处都是可见的。

一旦声明，全局变量就可以从此时起在文件中的任何位置使用！在上面的例子中，全局变量在函数和g_x中都使用。doSomething() main()

全局变量也可以在用户定义的命名空间内定义。下面是与上面相同的示例，但g_x已从全局范围移至用户定义的命名空间Foo：


```c++
#include <iostream>

namespace Foo // Foo is defined in the global scope
{
    int g_x {}; // g_x is now inside the Foo namespace, but is still a global variable
}

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    Foo::g_x = 3;
    std::cout << Foo::g_x << '\n';
}

int main()
{
    doSomething();
    std::cout << Foo::g_x << '\n';

    // global variables can be seen and used everywhere in the file
    Foo::g_x = 5;
    std::cout << Foo::g_x << '\n';

    return 0;
}
```

### 最好在命名空间内定义全局变量，而不是在全局命名空间中定义


### 全局变量具有静态持续时间

全局变量在程序启动时（开始执行之前）创建main()，并在程序结束时销毁。这称为静态持续时间。具有静态持续时间的变量有时称为静态变量。


### 命名全局变量（尤其是在全局命名空间中定义的变量）时，考虑使用“g”或“g_”前缀，以帮助将它们与局部变量和函数参数区分开来


## 7.6 内部链接

全局变量和函数标识符可以有internal linkage或external linkage。

具有**内部链接**的标识符可以在单个翻译单元内查看和使用，但无法从其他翻译单元访问。这意味着，如果两个源文件具有同名且具有**内部链接**的标识符，则这些标识符将被视为独立的（并且不会因具有重复定义而导致 ODR 违规）。


### 具有内部链接的全局变量

具有内部链接的全局变量有时也称为**内部变量**。

为了使非常量全局变量成为内部变量，我们使用**static**关键字。

Const 和 constexpr 全局变量默认具有内部链接（因此不需要static关键字——如果使用，它将被忽略）。

```c++
#include <iostream>

static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword

const int g_y{ 1 }; // const globals have internal linkage by default
constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default

int main()
{
    std::cout << g_x << ' ' << g_y << ' ' << g_z << '\n';
    return 0;
}
```

### 具有内部链接的功能

如上所述，函数标识符也有链接。函数默认为外部链接（我们将在下一课中介绍），但可以通过static关键字设置为内部链接：


```c++
// This function is declared as static, and can now be used only within this file
// Attempts to access it from another file via a function forward declaration will fail
[[maybe_unused]] static int add(int x, int y)
{
    return x + y;
}
```


### 单一定义规则和内部联系

我们注意到单一定义规则规定，一个对象或函数不能有多个定义，无论是在文件还是在程序中。

但是，值得注意的是，在不同文件中定义的内部对象（和函数）被视为独立实体（即使它们的名称和类型相同），因此不违反一次定义规则。每个内部对象只有一个定义。


### static与未命名的命名空间

在现代 C++ 中，使用关键字**static**为标识符提供内部链接的做法已不受欢迎。**未命名的命名空间**可以为更广泛的标识符（例如类型标识符）提供内部链接，并且更适合为许多标识符提供内部链接。


### 为什么要费心给标识符提供内部链接？

赋予标识符内部链接通常有两个原因：

- 我们希望确保某个标识符不被其他文件访问。这可能是一个我们**不想弄乱的全局变量**，或者是一个我们**不想调用的辅助函数**。
- 小心谨慎地避免命名冲突。由于具有内部链接的标识符不会暴露给链接器，因此它们只能与同一翻译单元中的名称发生冲突，而不会与整个程序中的名称发生冲突。
- 许多现代开发指南建议为每个不打算从其他文件使用的变量和函数提供内部链接。如果您有纪律，这是个不错的建议。

目前，我们至少建议采用一种更轻松的方法：为任何有明确理由禁止其他文件访问的标识符提供内部链接。



## 7.7 外部链接与变量前向声明

在上一课（7.6-内部链接）中，我们讨论了如何internal linkage将标识符的使用限制在单个文件中。在本课中，我们将探索的概念external linkage。

具有**外部链接**的标识符既可以在定义它的文件中看到和使用，也可以在其他代码文件中看到和使用（通过前向声明）。从这个意义上讲，具有外部链接的标识符是真正的“全局”标识符，因为它们可以在程序的任何地方使用！

### 函数默认具有外部链接

在课程2.8 — 具有多个代码文件的程序中，您了解到可以从一个文件中调用另一个文件中定义的函数。这是因为函数默认具有外部链接。

为了调用另一个文件中定义的函数，您必须 **forward declaration** 在希望使用该函数的任何其他文件中放置该函数的声明。前向声明会告知编译器该函数的存在，而链接器会将函数调用与实际函数定义连接起来。

a.cpp
```c++
#include <iostream>

void sayHi() // this function has external linkage, and can be seen by other files
{
    std::cout << "Hi!\n";
}
```

main.cpp
```c++
void sayHi(); // forward declaration for function sayHi, makes sayHi accessible in this file

int main()
{
    sayHi(); // call to function defined in another file, linker will connect this call to the function definition

    return 0;
}
```



### 具有外部链接的全局变量

具有外部链接的全局变量有时称为**外部变量**。要使全局变量成为外部变量（从而可被其他文件访问），我们可以使用关键字extern来实现：

非 const 全局变量默认是外部的，因此我们不需要将它们标记为**extern**。

```c++
int g_x { 2 }; // non-constant globals are external by default (no need to use extern)

extern const int g_y { 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_z { 3 }; // constexpr globals can be defined as extern, making them external (but this is pretty useless, see the warning in the next section)

int main()
{
    return 0;
}
```

### 通过 extern 关键字进行变量前向声明

要实际使用已在另一个文件中定义的外部全局变量，您还必须在 **forward declaration** 希望使用该变量的任何其他文件中为该全局变量放置一个。对于变量，创建前向声明也是通过关键字 **extern**（没有初始化值）完成的。

以下是使用变量前向声明的示例：

main.cpp

```c++
#include <iostream>

extern int g_x;       // this extern is a forward declaration of a variable named g_x that is defined somewhere else
extern const int g_y; // this extern is a forward declaration of a const variable named g_y that is defined somewhere else

int main()
{
    std::cout << g_x << ' ' << g_y << '\n'; // prints 2 3

    return 0;
}
```

这些变量的定义如下：

a.cpp：

```c++
// global variable definitions
int g_x { 2 };              // non-constant globals have external linkage by default
extern const int g_y { 3 }; // this extern gives g_y external linkage
```

在上面的例子中，a.cpp和main.cpp都引用了同一个全局变量，名为g_x。因此，尽管g_x在 中定义并初始化a.cpp，我们也可以main.cpp通过 的前向声明在 中使用它的值g_x。

请注意，**extern** 关键字在不同上下文中具有不同含义。在某些上下文中，**extern** 表示“赋予此变量外部链接”。在其他上下文中，表示“这是在其他地方定义的外部变量的前向声明”。是的，这很令人困惑，所以我们在第7.12 课——范围、持续时间和链接摘要 **extern** 中总结了所有这些用法。

### 最佳实践


仅extern用于全局变量前向声明或 const 全局变量定义。
不要将extern用于非 const 全局变量定义（它们是隐式的extern）。


## 7.9 内联函数和变量

### 现代 inline 关键字

在前面的章节中，我们提到**不要在头文件中实现（带有外部链接的）函数**，因为当这些头文件被包含到多个 .cpp 文件中时，函数定义将被复制到多个 .cpp 文件中。然后这些文件将被编译，链接器将抛出错误，因为它会注意到您多次定义了同一个函数，这违反了一次定义规则。

在现代 C++ 中，该术语 **inline** 已演变为“允许多次定义”。因此，内联函数是允许在多个翻译单元中定义的函数（不违反 ODR）。

内联函数有两个主要要求：

- 编译器需要能够在使用函数的每个翻译单元中看到内联函数的完整定义（前向声明本身是不够的）。如果还提供了前向声明，则定义可以在使用点之后出现。每个翻译单元只能出现一个这样的定义，否则将发生编译错误。

- 内联函数（具有外部链接，函数默认具有）的每个定义必须相同，否则会导致未定义的行为。

main.cpp
```c++
#include <iostream>

double circumference(double radius); // forward declaration

inline double pi() { return 3.14159; }

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}
```

math.cpp
```c++
inline double pi() { return 3.14159; }

double circumference(double radius)
{
    return 2.0 * pi() * radius;
}
```



### 规则

- 编译器需要能够在使用内联函数的任何地方看到其完整定义，并且内联函数（具有外部链接）的所有定义必须相同（否则会导致未定义的行为）。


## 7.10 跨多个文件共享全局常量（使用内联变量）

在C++17之前，以下是最简单、最常见的解决方案：

1. 创建一个头文件来保存这些常量
2. 在这个头文件中，定义一个命名空间（在第7.2 课--用户定义的命名空间和范围解析运算符中讨论过）
3. 在命名空间内添加所有常量（确保它们是constexpr）
4. #在需要的地方包含头文件

常量.h：

```c++
#ifndef CONSTANTS_H
#define CONSTANTS_H

// define your own namespace to hold constants
namespace constants
{
    // constants have internal linkage by default
    constexpr double pi { 3.14159 };
    constexpr double avogadro { 6.0221413e23 };
    constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}
#endif
```

### 全局常量作为内联变量C++17

在课程5.7 — 内联函数和变量中，我们介绍了内联变量，即可以有多个定义的变量，只要这些定义相同即可。通过使我们的 constexpr 变量成为内联变量，我们可以在头文件中定义它们，然后将它们 #include 到需要它们的任何 .cpp 文件中。这既避免了 ODR 违规，也避免了变量重复的弊端。

Constexpr 函数是隐式内联的，但 constexpr 变量不是隐式内联的。如果您想要一个内联 constexpr 变量，则必须将其显式标记为inline。

以下为C++17做法的正常操作

常量.h：

```c++
#ifndef CONSTANTS_H
#define CONSTANTS_H

// define your own namespace to hold constants
namespace constants
{
    inline constexpr double pi { 3.14159 }; // note: now inline constexpr
    inline constexpr double avogadro { 6.0221413e23 };
    inline constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}
#endif
```

### 关键见解

内联变量默认具有外部链接，因此它们对链接器可见。这是必要的，以便链接器可以消除重复定义。

非内联 constexpr 变量具有内部链接。如果包含在多个翻译单元中，则每个翻译单元将获得自己的变量副本。这不违反 ODR，因为它们不会暴露给链接器。


## 未命名和内联命名空间

### 未命名（匿名）命名空间

未命名命名空间（也称为匿名命名空间）是没有名称定义的命名空间，如下所示：

```c++
#include <iostream>

namespace // unnamed namespace
{
    void doSomething() // can only be accessed in this file
    {
        std::cout << "v1\n";
    }
}

int main()
{
    doSomething(); // we can call doSomething() without a namespace prefix

    return 0;
}
```

在未命名命名空间中声明的所有内容都被视为父命名空间的一部分。因此，即使函数doSomething()是在未命名命名空间中定义的，函数本身也可以从父命名空间（在本例中是全局命名空间）访问，这就是为什么我们可以在不使用任何限定符的doSomething()情况下进行调用main()。

这可能使未命名命名空间看起来毫无用处。但未命名命名空间的另一个影响是，未命名命名空间内的所有标识符都被视为具有内部链接，这意味着未命名命名空间的内容无法在定义未命名命名空间的文件之外看到。

对于函数来说，这实际上与将未命名命名空间中的所有函数定义为静态函数相同。以下程序实际上与上面的程序相同：

```c++
#include <iostream>

static void doSomething() // can only be accessed in this file
{
    std::cout << "v1\n";
}

int main()
{
    doSomething(); // we can call doSomething() without a namespace prefix

    return 0;
}
```

未命名命名空间通常用于当您有大量内容需要确保只保留在给定翻译单元本地时，因为将这些内容聚集在单个未命名命名空间中比单独将所有声明标记为 更容易static。未命名命名空间还会将程序定义的类型（我们将在后面的课程中讨论）保留在翻译单元本地，而没有其他等效机制可以做到这一点。

### 最佳实践

当您有想要保留在翻译单元本地的内容时，请选择未命名的命名空间。

避免在头文件中使用未命名的命名空间。