#include "../include/help.h"

int main()
{
    string str = "catmouse";
    str.replace(2, 4, "sz");//返回把 [2]~[2+(4-1)] 的内容替换为 "sz" 后的新字符串
    str.replace(2, 4, "abcd", 3);//返回把 [2]~[2+(4-1)] 的内容替换为 "abcd" 的前3个字符后的新字符串
    return 0;
}