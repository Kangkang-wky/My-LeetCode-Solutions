# debug

## 3.4 — 基本调试策略

### 调试策略 #1：注释掉代码

让我们从一个简单的问题开始。如果您的程序表现出错误的行为，减少需要搜索的代码量的一种方法是注释掉一些代码，看看问题是否仍然存在。如果问题仍然存在，注释掉的代码可能不是原因。


!提示

重复添加/删除或取消注释/注释调试语句的另一种方法是使用第三方库，该库允许您在代码中保留调试语句，但通过预处理器宏在发布模式下将其编译出来。dbg是一个这样的仅限头文件的库，它有助于实现这一点（通过DBG_MACRO_DISABLE预处理器宏）。

我们在第 5.7 课“内联函数和变量”中讨论仅包含头文件的库。

### 调试策略 #2：验证代码流

在更复杂的程序中常见的另一个问题是程序调用函数的次数过多或过少（包括根本没有调用）。

在这种情况下，将语句放在函数顶部以打印函数名称会很有帮助。这样，当程序运行时，你就可以看到调用了哪些函数。

当为了调试目的而打印信息时，**请使用 std::cerr 而不是 std::cout**。原因之一是 std::cout 可能被缓冲，这意味着在您要求 std::cout 输出信息和它实际输出信息之间可能会有暂停。如果您使用 std::cout 输出，然后程序立即崩溃，则 std::cout 可能尚未实际输出。这可能会误导您判断问题出在哪里。另一方面，std::cerr 是无缓冲的，这意味着您发送给它的任何东西都会立即输出。这有助于确保所有调试输出尽快出现（以牺牲一些性能为代价，而调试时我们通常不关心这些性能）。

使用 std::cerr 还可以帮助明确输出的信息是针对错误情况而不是正常情况。

### 调试策略 #3：打印值

由于某些类型的错误，程序可能会计算或传递错误的值。

我们还可以输出变量（包括参数）或表达式的值，以确保它们是正确的。

### 使用记录器

通过预处理器进行条件调试的另一种方法是将调试信息发送到日志。日志是已发生事件的顺序记录，通常带有时间戳。生成日志的过程称为日志记录。通常，日志被写入磁盘上的文件（称为日志文件），以便以后查看。大多数应用程序和操作系统都会编写日志文件，可用于帮助诊断发生的问题。

日志文件有几个优点。由于写入日志文件的信息与程序的输出是分开的，因此您可以避免因正常输出和调试输出混在一起而造成的混乱。日志文件还可以轻松发送给其他人进行诊断 - 因此，如果使用您的软件的人遇到问题，您可以要求他们将日志文件发送给您，这可能会帮助您找到问题所在。

C++ 包含一个名为的输出流std::clog，旨在用于写入日志信息。但是，默认情况下，它std::clog会写入标准错误流（与 相同std::cerr）。虽然您可以将其重定向到文件，但在这方面，您通常最好使用现有的众多第三方日志记录工具之一。使用哪一个取决于您。

为了便于说明，我们将展示使用plog记录器输出到记录器的样子。Plog 是作为一组头文件实现的，因此很容易将其包含在您需要的任何地方，而且它重量轻且易于

### 不要犯错误

好吧，最好的办法是从一开始就不要犯错误。以下是一些可以帮助避免犯错的方法：

遵循最佳实践。
疲劳或沮丧时不要编程。休息一下，稍后再回来。
了解语言中常见的陷阱（所有那些我们警告您不要做的事情）。
不要让你的函数太长。
如果可能的话，最好使用标准库而不是编写自己的代码。
自由地注释你的代码。
从简单的解决方案开始，然后逐步增加复杂性。
避免使用聪明/不明显的解决方案。
优化可读性和可维护性，而不是性能。