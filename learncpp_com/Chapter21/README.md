## 21.13 — 浅复制与深复制

### 浅复制

由于 C++ 对您的类了解不多，因此它提供的默认复制构造函数和默认赋值运算符使用一种称为成员逐一复制（也称为浅复制）的复制方法。这意味着 C++ 分别复制类的每个成员（对重载的 operator= 使用赋值运算符，对复制构造函数使用直接初始化）。当类很简单（例如不包含任何动态分配的内存）时，这种方法非常有效。

编译器为该类提供的默认复制构造函数和默认赋值运算符如下所示：

```c++
#include <cassert>
#include <iostream>

class Fraction
{
private:
    int m_numerator { 0 };
    int m_denominator { 1 };

public:
    // Default constructor
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator{ numerator }
        , m_denominator{ denominator }
    {
        assert(denominator != 0);
    }

    // Possible implementation of implicit copy constructor
    Fraction(const Fraction& f)
        : m_numerator{ f.m_numerator }
        , m_denominator{ f.m_denominator }
    {
    }

    // Possible implementation of implicit assignment operator
    Fraction& operator= (const Fraction& fraction)
    {
        // self-assignment guard
        if (this == &fraction)
            return *this;

        // do the copy
        m_numerator = fraction.m_numerator;
        m_denominator = fraction.m_denominator;

        // return the existing object so we can chain this operator
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Fraction& f1)
    {
	out << f1.m_numerator << '/' << f1.m_denominator;
	return out;
    }
};
```

#### 注意

然而，在设计处理动态分配内存的类时，成员（浅）复制会给我们带来很多麻烦！这是因为指针的浅拷贝只复制指针的地址——它不分配任何内存或复制指向的内容！

让我们来看一个例子：

```c++
#include <cstring> // for strlen()
#include <cassert> // for assert()

class MyString
{
private:
    char* m_data{};
    int m_length{};

public:
    MyString(const char* source = "" )
    {
        assert(source); // make sure source isn't a null string

        // Find the length of the string
        // Plus one character for a terminator
        m_length = std::strlen(source) + 1;

        // Allocate a buffer equal to this length
        m_data = new char[m_length];

        // Copy the parameter string into our internal buffer
        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source[i];
    }

    ~MyString() // destructor
    {
        // We need to deallocate our string
        delete[] m_data;
    }

    char* getString() { return m_data; }
    int getLength() { return m_length; }
};
```

上面是一个简单的字符串类，它分配内存来保存我们传入的字符串。请注意，我们没有定义复制构造函数或重载赋值运算符。因此，C++ 将提供执行浅拷贝的默认复制构造函数和默认赋值运算符。复制构造函数将如下所示：

```c++
MyString::MyString(const MyString& source)
    : m_length { source.m_length }
    , m_data { source.m_data }
{
}
```

请注意，m_data 只是 source.m_data 的浅指针副本，这意味着它们现在都指向同一个东西。


### 深度复制

解决此问题的一个方法是对要复制的任何非空指针进行深度复制。**深度复制** 会为副本分配内存，然后复制实际值，这样副本就位于与源不同的内存中。这样，副本和源就不同，不会以任何方式相互影响。进行深度复制需要我们编写自己的复制构造函数和重载赋值运算符。

让我们继续展示如何为 MyString 类完成此操作：

```c++
// assumes m_data is initialized
void MyString::deepCopy(const MyString& source)
{
    // first we need to deallocate any value that this string is holding!
    delete[] m_data;

    // because m_length is not a pointer, we can shallow copy it
    m_length = source.m_length;

    // m_data is a pointer, so we need to deep copy it if it is non-null
    if (source.m_data)
    {
        // allocate memory for our copy
        m_data = new char[m_length];

        // do the copy
        for (int i{ 0 }; i < m_length; ++i)
            m_data[i] = source.m_data[i];
    }
    else
        m_data = nullptr;
}

// Copy constructor
MyString::MyString(const MyString& source)
{
    deepCopy(source);
}
```


现在让我们来做重载赋值运算符。重载赋值运算符稍微有点棘手：

```c++
// Assignment operator
MyString& MyString::operator=(const MyString& source)
{
    // check for self-assignment
    if (this != &source)
    {
        // now do the deep copy
        deepCopy(source);
    }

    return *this;
}
```

请注意，我们的赋值运算符与我们的复制构造函数非常相似，但有三个主要区别：

- 我们添加了自我分配检查。
- 我们返回 *this 以便我们可以链接赋值运算符。
- 我们需要明确释放字符串中已经持有的任何值（这样当 m_data 稍后重新分配时就不会发生内存泄漏）。这在 deepCopy() 中处理。

当调用重载赋值运算符时，被赋值的项可能已经包含先前的值，我们需要确保在为新值分配内存之前清理该值。对于非动态分配的变量（固定大小），我们不必担心，因为新值只会覆盖旧值。但是，对于动态分配的变量，我们需要在分配任何新内存之前明确释放任何旧内存。如果我们不这样做，代码不会崩溃，但每次进行赋值时都会发生内存泄漏，这会消耗掉我们的可用内存！


### 三法则

还记得三的规则吗？如果一个类需要用户定义的析构函数、复制构造函数或复制赋值运算符，那么它可能需要这三个。这就是原因。如果我们用户定义这些函数中的任何一个，可能是因为我们正在处理动态内存分配。我们需要复制构造函数和复制赋值来处理深度复制，以及析构函数来释放内存。
