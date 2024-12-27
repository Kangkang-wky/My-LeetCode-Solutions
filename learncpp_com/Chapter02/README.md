## 2.12 — Header guards

- 好消息是，我们可以通过一种称为header guard（也称为include guard）的机制来避免上述问题。header guard 是条件编译指令，其形式如下：

```c++
#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

// your declarations (and certain types of definitions) here

#endif
```

当此标头被 #included 时，预处理器将检查此翻译单元中是否已定义SOME_UNIQUE_NAME_HERE 。如果这是我们第一次包含标头，则SOME_UNIQUE_NAME_HERE将尚未定义。因此，它会 #define SOME_UNIQUE_NAME_HERE并包含文件的内容。如果标头再次包含到同一个文件中，则SOME_UNIQUE_NAME_HERE将在第一次包含标头内容时就已经定义，并且标头的内容将被忽略（感谢 #ifndef）。


### pragma once

现代编译器支持使用预处理器指令的更简单的替代形式的头保护#pragma：

```c++
#pragma once

// your code here
```

头文件保护的目的是确保给定头文件的内容不会被复制到任何单个文件中超过一次，以防止重复定义。

重复声明是可以的——但即使你的头文件由所有声明（没有定义）组成，包含头文件保护仍然是最佳做法。

请注意，头文件保护不会阻止将头文件的内容（一次）复制到单独的项目文件中。这是一件好事，因为我们经常需要从不同的项目文件中引用给定头文件的内容。