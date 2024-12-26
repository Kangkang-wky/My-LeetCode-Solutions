## 14.12 — 委托构造函数




## 14.13 — 临时类对象

同样的问题也适用于类类型的上下文。

下面的示例与上面的例子类似，但是使用程序定义的类类型IntPair而不是int：

```c++
#include <iostream>

class IntPair
{
private:
    int m_x{};
    int m_y{};

public:
    IntPair(int x, int y)
        : m_x { x }, m_y { y }
    {}

    int x() const { return m_x; }
    int y() const { return m_y; }
};

void print(IntPair p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

int main()
{
    // Case 1: Pass variable
    IntPair p { 3, 4 };
    print(p); // prints (3, 4)

    return 0;
}
```

在情况 1 中，我们实例化变量IntPair p，然后传递p给函数print()。

但是，p仅使用一次，并且函数print()将接受右值，因此实际上没有理由在这里定义变量。所以让我们摆脱p。

我们可以通过传递临时对象而不是命名变量来实现这一点。**临时对象**（有时称为**匿名对象**或**未命名对象**）是没有名称且仅在单个表达式的持续时间内存在的对象。

创建临时类类型对象有两种常用方法：

```c++
#include <iostream>

class IntPair
{
private:
    int m_x{};
    int m_y{};

public:
    IntPair(int x, int y)
        : m_x { x }, m_y { y }
    {}

    int x() const { return m_x; }
    int y() const{ return m_y; }
};

void print(IntPair p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

int main()
{
    // Case 1: Pass variable
    IntPair p { 3, 4 };
    print(p);

    // Case 2: Construct temporary IntPair and pass to function
    print(IntPair { 5, 6 } );

    // Case 3: Implicitly convert { 7, 8 } to a temporary Intpair and pass to function
    print( { 7, 8 } );

    return 0;
}
```

### 临时对象和按值返回

当函数按值返回时，返回的对象是一个临时对象（使用 return 语句中标识的值或对象进行初始化）。

以下是一些示例：

```c++
#include <iostream>

class IntPair
{
private:
    int m_x{};
    int m_y{};

public:
    IntPair(int x, int y)
        : m_x { x }, m_y { y }
    {}

    int x() const { return m_x; }
    int y() const { return m_y; }
};

void print(IntPair p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

// Case 1: Create named variable and return
IntPair ret1()
{
    IntPair p { 3, 4 };
    return p; // returns temporary object (initialized using p)
}

// Case 2: Create temporary IntPair and return
IntPair ret2()
{
    return IntPair { 5, 6 }; // returns temporary object (initialized using another temporary object)
}

// Case 3: implicitly convert { 7, 8 } to IntPair and return
IntPair ret3()
{
    return { 7, 8 }; // returns temporary object (initialized using another temporary object)
}

int main()
{
    print(ret1());
    print(ret2());
    print(ret3());

    return 0;
}
```

## 14.14 — 拷贝构造函数简介

### 复制构造函数的参数必须是引用

要求复制构造函数的参数是左值引用或 const 左值引用。由于复制构造函数不应修改参数，因此最好使用 const 左值引用。

- 最佳实践： 如果您编写自己的复制构造函数，则该参数应该是 const 左值引用。


### 复制构造函数的参数必须是 (const) 引用。为什么我们不允许使用按值传递？

当我们通过值传递类类型参数时，将隐式调用复制构造函数将参数复制到参数中。

如果复制构造函数使用按值传递，则复制构造函数需要调用自身以将初始化器参数复制到复制构造函数参数中。但对复制构造函数的调用也将按值传递，因此将再次调用复制构造函数以将参数复制到函数参数中。这将导致对复制构造函数的无限调用链。
