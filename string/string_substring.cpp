#include "../include/help.h"


int main()
{
    string str = "catmouse";
    str.substr(3); //返回 [3] 及以后的子串
    str.substr(2, 4); //返回 str[2]~str[2+(4-1)] 子串(即从[2]开始4个字符组成的字符串)
    return 0;
}