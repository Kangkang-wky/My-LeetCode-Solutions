## 7.3 局部变量






## 外部链接与变量前向声明

在上一课（7.6-内部链接）中，我们讨论了如何internal linkage将标识符的使用限制在单个文件中。在本课中，我们将探索的概念external linkage。

具有外部链接的标识符既可以在定义它的文件中看到和使用，也可以在其他代码文件中看到和使用（通过前向声明）。从这个意义上讲，具有外部链接的标识符是真正的“全局”标识符，因为它们可以在程序的任何地方使用！

### 函数默认具有外部链接

在课程2.8 — 具有多个代码文件的程序中，您了解到可以从一个文件中调用另一个文件中定义的函数。这是因为函数默认具有外部链接。

为了调用另一个文件中定义的函数，您必须forward declaration在希望使用该函数的任何其他文件中放置该函数的声明。前向声明会告知编译器该函数的存在，而链接器会将函数调用与实际函数定义连接起来。

### 具有外部链接的全局变量

具有外部链接的全局变量有时称为外部变量。要使全局变量成为外部变量（从而可被其他文件访问），我们可以使用关键字extern来实现：

非 const 全局变量默认是外部的（如果使用，extern关键字将被忽略）。

#### 通过 extern 关键字进行变量前向声明

要实际使用已在另一个文件中定义的外部全局变量，您还必须在forward declaration希望使用该变量的任何其他文件中为该全局变量放置一个。对于变量，创建前向声明也是通过关键字extern（没有初始化值）完成的。


## 7.9 — 跨多个文件共享全局常量（使用内联变量）

在C++17之前，以下是最简单、最常见的解决方案：

创建一个头文件来保存这些常量
在这个头文件中，定义一个命名空间（在第7.2 课--用户定义的命名空间和范围解析运算符中讨论过）
在命名空间内添加所有常量（确保它们是constexpr）
#在需要的地方包含头文件

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




