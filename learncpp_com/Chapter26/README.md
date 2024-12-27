# README
## template class

拆分模板类

模板不是类或函数——它是用于创建类或函数的模板。因此，它的工作方式与普通函数或类不太一样。在大多数情况下，这不是什么大问题。然而，有一个领域通常会给开发人员带来问题。

对于非模板类，常见的做法是将类定义放在头文件中，将成员函数定义放在同名的代码文件中。这样，成员函数定义就会被编译为单独的项目文件。但是，对于模板，这种方法行不通。

就像函数模板一样，只有当类模板在翻译单元中使用（例如作为 intArray 等对象的类型）时，编译器才会实例化类模板。为了执行实例化，编译器必须看到完整的类模板定义（而不仅仅是声明）和所需的特定模板类型。

还要记住，C++ 是单独编译文件的。编译 main.cpp 时，Array.h 头文件的内容（包括模板类定义）会被复制到 main.cpp 中。当编译器发现我们需要两个模板实例 Array<int> 和 Array<double> 时，它会实例化它们，并将它们编译为 main.cpp 翻译单元的一部分。由于operator[]成员函数有声明，因此编译器会接受对它的调用，假设它会在其他地方定义。

当单独编译 Array.cpp 时，Array.h 头的内容会被复制到 Array.cpp 中，但编译器不会在 Array.cpp 中找到任何需要Array<int>::operator[]实例化 Array 类模板或函数模板的代码 - 因此它不会实例化任何东西。

因此，当程序链接时，我们会收到链接器错误，因为 main.cpp 调用了Array<int>::operator[]该模板函数但从未实例化！

在编译的时候做显式实例化的声明和定义来避免这个问题

## 26.2 — 模板非类型参数

在之前的课程中，您学习了如何使用模板类型参数来创建类型独立的函数和类。模板类型参数是一种占位符类型，用于替换作为参数传入的类型。

但是，模板类型参数并不是唯一可用的模板参数类型。模板类和函数可以使用另一种类型的模板参数，即非类型参数。

非类型参数

模板非类型参数是一种模板参数，其中参数的类型是预定义的，并替换作为参数传入的 constexpr 值。

非类型参数可以是以下任意类型：

- 整数类型
- 枚举类型
- 指向类对象的指针或引用
- 指向函数的指针或引用
- 指向类成员函数的指针或引用
- std::nullptr_t
- 浮点类型（自 C++20 起）

## 26.3 — 函数模板特化

实现类似结果的另一种方法是使用显式模板特化。**显式模板特化**（通常缩写为**模板特化**）是一种功能，它允许我们为特定类型或值显式定义模板的不同实现。当所有模板参数都经过特化时，这称为**完全特化**。当只有部分模板参数经过特化时，这称为**部分特化**。


```c++
#include <iostream>

// Here's our primary template (must come first)
template <typename T>
void print(const T& t)
{
    std::cout << t << '\n';
}

// A full specialization of primary template print<T> for type double
// Full specializations are not implicitly inline, so make this inline if put in header file
template<>                          // template parameter declaration containing no template parameters
void print<double>(const double& d) // specialized for type double
{
    std::cout << std::scientific << d << '\n';
}

int main()
{
    print(5);
    print(6.7);

    return 0;
}
```


## 26.4 — 类模板特化


### 类模板特化


```c++
#include <cstdint>

// First define our non-specialized class template
template <typename T>
class Storage8
{
private:
    T m_array[8];

public:
    void set(int index, const T& value)
    {
        m_array[index] = value;
    }

    const T& get(int index) const
    {
        return m_array[index];
    }
};

// Now define our specialized class template
template <> // the following is a template class with no templated parameters
class Storage8<bool> // we're specializing Storage8 for bool
{
// What follows is just standard class implementation details

private:
    std::uint8_t m_data{};

public:
    // Don't worry about the details of the implementation of these functions
    void set(int index, bool value)
    {
        // Figure out which bit we're setting/unsetting
        // This will put a 1 in the bit we're interested in turning on/off
        auto mask{ 1 << index };

        if (value)  // If we're setting a bit
            m_data |= mask;   // use bitwise-or to turn that bit on
        else  // if we're turning a bit off
            m_data &= ~mask;  // bitwise-and the inverse mask to turn that bit off
	}

    bool get(int index)
    {
        // Figure out which bit we're getting
        auto mask{ 1 << index };
        // bitwise-and to get the value of the bit we're interested in
        // Then implicit cast to boolean
        return (m_data & mask);
    }
};

// Same example as before
int main()
{
    // Define a Storage8 for integers (instantiates Storage8<T>, where T = int)
    Storage8<int> intStorage;

    for (int count{ 0 }; count < 8; ++count)
    {
        intStorage.set(count, count);
	}

    for (int count{ 0 }; count < 8; ++count)
    {
        std::cout << intStorage.get(count) << '\n';
    }

    // Define a Storage8 for bool  (instantiates Storage8<bool> specialization)
    Storage8<bool> boolStorage;

    for (int count{ 0 }; count < 8; ++count)
    {
        boolStorage.set(count, count & 3);
    }

	std::cout << std::boolalpha;

    for (int count{ 0 }; count < 8; ++count)
    {
        std::cout << boolStorage.get(count) << '\n';
    }

    return 0;
}
```