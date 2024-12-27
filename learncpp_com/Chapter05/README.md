
### 条件运算符

condition ? expression1 : expression2;

greater = ((x > y) ? x : y);

尽可能在简单的表达式中使用这样的三目操作符


## 5.8 — std::string_view 简介

std::string为了解决初始化（或复制）成本高昂的问题，C++17 引入了std::string_view（位于 <string_view> 标头中）。提供对现有字符串（C 样式字符串、或其他）std::string_view的只读访问，而无需进行复制。**只读**意味着我们可以访问和使用正在查看的值，但不能修改它。std::stringstd::string_view


```c++
#include <iostream>
#include <string_view> // C++17

// str provides read-only access to whatever argument is passed in
void printSV(std::string_view str) // now a std::string_view
{
    std::cout << str << '\n';
}

int main()
{
    std::string_view s{ "Hello, world!" }; // now a std::string_view
    printSV(s);

    return 0;
}
```


该程序产生与前一个程序相同的输出，但没有复制字符串“Hello, world!”。

当我们std::string_view s使用 C 风格的字符串文字进行初始化时"Hello, world!"，s提供对“Hello, world!”的只读访问，而无需复制字符串。当我们传递s给 时printSV()，参数str从 初始化s。这允许我们通过 访问“Hello, world!” str，同样无需复制字符串。


### 最佳实践

当您需要只读字符串时，尤其是对于函数参数，最好使用std::string_view。std::string