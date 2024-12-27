## 9.3 — C++ 中的常见语义错误

### 整数除法

在下面的例子中，我们想要进行浮点除法，但是因为两个操作数都是整数，所以我们最终进行了整数除法：

```c++
#include <iostream>

int main()
{
    int x{ 5 };
    int y{ 3 };

    std::cout << x << " divided by " << y << " is: " << x / y << '\n'; // integer division

    return 0;
}
```

### 意外的空语句

注意不小心引入的 nullptr 空指针问题

```c++
#include <iostream>

void blowUpWorld()
{
    std::cout << "Kaboom!\n";
}

int main()
{
    std::cout << "Should we blow up the world again? (y/n): ";
    char c{};
    std::cin >> c;

    if (c == 'y');     // accidental null statement here
        blowUpWorld(); // so this will always execute since it's not part of the if-statement

    return 0;
}
```

### 调用函数时忘记使用函数调用运算符

```c++
#include <iostream>

int getValue()
{
    return 5;
}

int main()
{
    std::cout << getValue << '\n';

    return 0;
}
```

## 9.6 — Assert 和 static_assert

### Assert

使用条件语句来检测无效参数（或验证某种其他类型的假设），以及打印错误消息并终止程序，是一种检测问题的常用方法，因此 C++ 提供了一种快捷方法来执行此操作。

断言是一种表达式，除非程序中有错误，否则它将为真。如果表达式的计算结果为true，则断言语句不执行任何操作。如果条件表达式的计算结果为false，则显示错误消息并终止程序（通过std::abort）。此错误消息通常包含失败的表达式（以文本形式），以及代码文件的名称和断言的行号。这样不仅可以很容易地判断问题是什么，还可以很容易地判断问题发生在代码中的哪个位置。这可以极大地帮助调试工作。

```c++
assert(found && "Car could not be found in database");
```

### static_assert

C++ 还有另一种类型的断言，称为static_assert。static_assert是在编译时而不是运行时检查的断言，失败static_assert会导致编译错误。与在 <cassert> 标头中声明的 assert 不同， static_assert 是一个关键字，因此无需包含标头即可使用它。

一些有用的说明static_assert：

因为static_assert由编译器评估，所以条件必须是常量表达式。
static_assert可以放在代码文件的任何位置（甚至是全局命名空间）。
static_assert在发布版本中不会被停用（像正常assert情况一样）。

```c++
static_assert(sizeof(long) == 8, "long must be 8 bytes");
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

int main()
{
	return 0;
}
```