## 8.4 — Constexpr if 语句

C++17 引入了constexpr if 语句，该语句要求条件为常量表达式。 constexpr-if 语句的条件将在编译时进行评估。

如果 constexpr 条件表达式求值为true，则整个 if-else 将被 true-statement 替换。如果 constexpr 条件表达式求值为false，则整个 if-else 将被 false-statement 替换（如果存在）或不替换（如果没有 else）。

要使用 constexpr-if 语句, if constexpr 语句使用

## 8.12 —  =暂停（提早退出程序）

### std::exit() 函数

std::exit()是导致程序正常终止的函数。正常终止意味着程序以预期的方式退出。请注意，该术语normal termination并不意味着程序是否成功（这就是 的用途status code）。例如，假设您正在编写一个程序，您希望用户输入要处理的文件名。如果用户输入了无效的文件名，您的程序可能会返回非零值status code以指示失败状态，但它仍然会有一个normal termination。

std::exit()执行一系列清理功能。首先，销毁具有静态存储持续时间的对象。然后，如果使用了任何文件，则进行其他一些杂项文件清理。最后，将控制权返回给操作系统，并将传递给的参数std::exit()用作status code。

### 显式调用 std::exit()

虽然在函数返回std::exit()后隐式调用，但也可以显式调用以在程序正常终止之前暂停程序。当以这种方式调用时，您需要包含标头。main()std::exit()std::exit()cstdlib

关键见解

std::exitmain()返回时被隐式调用。

### std::exit()不清理局部变量

关于显式调用的一个重要注意事项std::exit()：std::exit()不会清理任何局部变量（无论是在当前函数中，还是在调用堆栈中的函数中）。这意味着，std::exit()如果您的程序依赖于任何局部变量的自我清理，则调用可能会很危险。

警告

该std::exit()函数不会清理当前函数中的局部变量或调用堆栈。