#include "../include/help.h"

void* my_memmove(void* dest, void* src, size_t num)
{
    // 判断 dest 与 src 是否为 NULL
	assert(dest && src);

    // 给予返回值 ret
	void* ret = dest;

	// assert 判断指针是否为空
	if (dest < src)
	{
		// 前->后
		while (num--) // 即模拟实现 memcpy 的函数代码
		{
			*(reinterpret_cast<char*>(dest)) = *(reinterpret_cast<char*>(src));
			dest = reinterpret_cast<char*>(dest) + 1;
			src = reinterpret_cast<char*>(src) + 1;
		}
	}
	else
	{
		// 后->前
		while (num--)
		{
			*(reinterpret_cast<char*>(dest) + num) = *(reinterpret_cast<char*>(src) + num); // 每次 num--，实现后->前拷贝
		}
	}
	return ret;
}
