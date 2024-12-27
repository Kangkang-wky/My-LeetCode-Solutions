## 10.7 Typedef 和类型别名

### 类型别名

在 C++ 中，using是一个为现有数据类型创建别名的关键字。要创建这样的类型别名，我们使用关键字using，后跟类型别名的名称，后跟等号和现有数据类型。例如：

```c++
#include <iostream>

int main()
{
    using Distance = double; // define Distance as an alias for type double

    Distance milesToDestination{ 3.4 }; // defines a variable of type double

    std::cout << milesToDestination << '\n'; // prints a double value

    return 0;
}
```