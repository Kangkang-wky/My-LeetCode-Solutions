#include "../include/help.h"

int main()
{
    string str = "catmouseadd";
    str.erase(3);//删除 [3] 及以后的字符，并返回新字符串
    str.erase(3, 5);//删除从 [3] 开始的 5 个字符，并返回新字符串
    return 0;
}