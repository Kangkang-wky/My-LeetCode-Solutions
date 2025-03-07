#include "../include/help.h"

/**
 * @brief memory move 操作
 * 
 * @param dest 
 * @param src 
 * @param num 
 * @return void* 
 */

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
		while (num--)
		{
            // 即模拟实现 memcpy 的函数代码
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
            // 每次 num--，实现后->前拷贝
			*(reinterpret_cast<char*>(dest) + num) = *(reinterpret_cast<char*>(src) + num); 
		}
	}
	return ret;
}

/**
 * @brief memory copy 操作
 * 
 * @param dest 
 * @param src 
 * @param num 
 * @return void* 
 */


void* my_memcpy(void* dest, const void* src, size_t num) {
	assert(dest && src);

	int i = 0;
	
	void* ret = dest;
	// num单位为字节（而非元素)
	// 注意此处是字节数量
	while (num--) {
		// 逐字节拷贝
		*((char*)dest) = *((char*)src);
		src = (char*)src + 1;
		dest = (char*)dest + 1;
	}
	// 返回拷贝的目标空间的起始地址
	return ret;
}