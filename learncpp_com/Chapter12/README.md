## compound data types 复合数据类型

C++ supports the following compound types:

Functions
Arrays
Pointer types:
    Pointer to object
    Pointer to function
Pointer to member types:
    Pointer to data member
    Pointer to member function
Reference types:
    L-value references
    R-value references
Enumerated types:
    Unscoped enumerations
    Scoped enumerations
Class types:
    Structs
    Classes
    Unions

## 12.2 — 值类别（左值和右值）

### 表达式的值类别

答案在于表达式的第二个属性：value category。表达式（或子表达式）的值类别指示表达式是否解析为值、函数或某种对象。

在 C++11 之前，只有两种可能的值类别：lvalue和rvalue。

在 C++11 中，添加了三个附加值类别（glvalue、prvalue和xvalue）来支持称为 的新功能move semantics。

作者注

在本课中，我们将坚持使用 C++11 之前的值类别视图，因为这可以更轻松地介绍值类别（并且是我们目前所需要的）。我们将在后续章节中介绍移动语义（以及另外三个值类别）。


左值（发音为“ell-value”，是“left value”或“locator value”的缩写，有时写为“l-value”）是一个计算结果为可识别对象或函数（或位域）的表达式。

C++ 标准使用了“身份”一词，但定义不明确。具有身份的实体（如对象或函数）可以与其他类似实体区分开来（通常通过比较实体的地址）。

具有身份的实体可以通过标识符、引用或指针进行访问，并且其寿命通常比单个表达式或语句更长。

```c++
int main()
{
    int x { 5 };
    int y { x }; // x is an lvalue expression

    return 0;
}
```

在上面的程序中，表达式x是一个左值表达式，因为它计算的是变量x（有一个标识符）。

自从语言中引入常量以来，左值就分为两种子类型：可修改左值是其值可以修改的左值。不可修改左值是其值不能修改的左值（因为左值是 const 或 constexpr）。

```c++
int main()
{
    int x{};
    const double d{};

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression

    return 0;
}
```

右值（发音为“arr-value”，是“right value”的缩写，有时写作r-value）是一种非左值的表达式。右值表达式求值为一个值。常见的右值包括文字（C 样式字符串文字除外，它们是左值）以及按值返回的函数和运算符的返回值。右值不可识别（意味着必须立即使用），并且仅存在于使用它们的表达式的范围内。

```c++
int return5()
{
    return 5;
}

int main()
{
    int x{ 5 }; // 5 is an rvalue expression
    const double d{ 1.2 }; // 1.2 is an rvalue expression

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression
    int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)

    int w { x + 1 }; // x + 1 is an rvalue expression
    int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression

    return 0;
}
```

### 关键见解

**左值表达式计算结果为可识别的对象。**
**右值表达式计算结果为一个值。**

相关内容

左值和右值表达式的完整列表可在此处找到。在 C++11 中，右值分为两个子类型：prvalues 和 xvalues，因此我们在此处讨论的右值是这两个类别的总和。

**小技巧：取地址，编译过了就是左值， 编译没有通过就是右值**

```c++
int foo()
{
    return 5;
}

int main()
{
    int x { 5 };
    &x; // compiles: x is an lvalue expression
    &5; // doesn't compile: 5 is an rvalue expression
    &foo(); // doesn't compile: foo() is an rvalue expression
}
```

### 经验法则

识别左值和右值表达式的经验法则：

左值表达式是那些计算结果为函数或可识别对象（包括变量）且在表达式结束后仍然存在的表达式。
右值表达式是那些计算结果为值的表达式，包括在表达式结束后不再存在的文字和临时对象。


## 12.3 — 左值引用

左值引用类型

左值引用（通常称为，reference因为在 C++11 之前只有一种引用类型）充当现有左值（例如变量）的别名。

要声明左值引用类型，我们在类型声明中使用与号 (&)：

```c++
int      // a normal int type
int&     // an lvalue reference to an int object
double&  // an lvalue reference to a double object
```

左值引用的初始化

**与常量非常相似，所有引用都必须初始化。**


无法重新设置引用（更改为引用另一个对象）

一旦初始化，C++ 中的引用就无法重新定位，这意味着它无法更改为引用另一个对象。

新的 C++ 程序员经常尝试通过使用赋值来为引用提供另一个要引用的变量来重新定位引用。这将编译并运行 - 但不会按预期运行。考虑以下程序：

```c++
#include <iostream>

int main()
{
    int x { 5 };
    int y { 6 };

    int& ref { x }; // ref is now an alias for x

    ref = y; // assigns 6 (the value of y) to x (the object being referenced by ref)
    // The above line does NOT change ref into a reference to variable y!

    std::cout << x << '\n'; // user is expecting this to print 5

    return 0;
}
```

引用不是对象

可能令人惊讶的是，在 C++ 中引用不是对象。引用不需要存在或占用存储空间。如果可能，编译器会通过将所有出现的引用替换为引用对象来优化引用。然而，这并不总是可行的，在这种情况下，引用可能需要存储空间。

这也意味着“引用变量”这个术语有点用词不当，因为变量是具有名称的对象，而引用不是对象。

因为引用不是对象，所以它们不能在任何需要对象的地方使用（例如，你不能引用引用，因为左值引用必须引用可识别的对象）。在你需要一个对象引用或一个可以重新放置的引用的情况下std::reference_wrapper（我们将在第23.3 课-聚合中介绍），它提供了一个解决方案。

## 12.4 — 对 const 的左值引用

对 const 的左值引用

通过在声明左值引用时使用const关键字，我们告诉左值引用将其引用的对象视为 const。这样的引用称为对 const 值的左值引用（有时称为对 const 的引用或const 引用）。

对 const 的左值引用可以绑定到不可修改的左值：

```c++
int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    return 0;
}
```

```c++
#include <iostream>

int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    std::cout << ref << '\n'; // okay: we can access the const object
    ref = 6;                  // error: we can not modify an object through a const reference

    return 0;
}
```

最佳实践

除非您需要修改所引用的对象，否则优先选择lvalue references to const。lvalue references to non-const


## 12.6 — 通过 const 左值引用传递

最佳实践

根据经验法则，通过值传递基本类型，通过 const 引用传递类（或结构）类型。

其他常见的按值传递类型：枚举类型和std::string_view。
其他常见的按（const）引用传递类型：std::string、std::array和std::vector。

## 12.7 — 指针简介

引用必须初始化，指针不需要初始化（但应该初始化）。
引用不是对象，指针才是。
引用不能被重新放置（更改为引用其他内容），指针可以改变它们指向的内容。
引用必须始终绑定到某个对象，指针可以指向虚无（我们将在下一课中看到一个例子）。
引用是“安全的”（悬垂引用之外），指针本质上是危险的（我们也将在下一课中讨论这个问题）。

## 12.10 — 通过地址传递

三种方式：  按值传递（2.4 -- 函数形参和实参简介）和按引用传递（12.5 -- 按左值引用传递）。
C++ 提供了第三种将值传递给函数的方法，称为按地址传递。使用按地址传递时，调用者不再提供对象作为参数，而是提供对象的地址（通过指针）

```c++
#include <iostream>
#include <string>

void printByValue(std::string val) // The function parameter is a copy of str
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string& ref) // The function parameter is a reference that binds to str
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const std::string* ptr) // The function parameter is a pointer that holds the address of str
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str

    return 0;
}
```

按地址传递的时候一定要注意空指针的问题：这个地方非常的危险

如果永远不应该将空指针传递给函数，则可以使用assert（我们在第9.6 课 - Assert 和 static_assert中介绍过）（因为断言旨在记录永远不会发生的事情）

### 优先通过（const）引用传递

请注意，上面示例中的函数print()不能很好地处理空值——它实际上只是中止了该函数。鉴于此，为什么允许用户传入空值呢？通过引用传递具有与通过地址传递相同的好处，而没有无意中取消引用空指针的风险。

通过 const 引用传递比通过地址传递还有其他一些优点。

首先，因为通过地址传递的对象必须有地址，所以只有左值可以通过地址传递（因为右值没有地址）。通过 const 引用传递更灵活，因为它可以接受左值和右值：

```c++
#include <iostream>

void printByValue(int val) // The function parameter is a copy of the argument
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const int& ref) // The function parameter is a reference that binds to the argument
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const int* ptr) // The function parameter is a pointer that holds the address of the argument
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    printByValue(5);     // valid (but makes a copy)
    printByReference(5); // valid (because the parameter is a const reference)
    printByAddress(&5);  // error: can't take address of r-value

    return 0;
}
```

## 12.12 — 按引用返回和按地址返回


### 不要通过引用返回非常量静态局部变量

```c++
#include <iostream>
#include <string>

const int& getNextId()
{
    static int s_x{ 0 }; // note: variable is non-const
    ++s_x; // generate the next id
    return s_x; // and return a reference to it
}

int main()
{
    const int& id1 { getNextId() }; // id1 is a reference
    const int& id2 { getNextId() }; // id2 is a reference

    std::cout << id1 << id2 << '\n';

    return 0;
}
```