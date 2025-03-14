#include "../include/help.h"


int main()
{
    string str = "catmouse";
    str.insert(2, "sz");//从 [2] 位置开始添加字符串 "sz"，并返回形成的新字符串
    str.insert(2, "abcd", 3);//从 [2] 位置开始添加字符串 "abcd" 的前 3 个字符，并返回形成的新字符串
    str.insert(2, "abcd", 1, 3);//从 [2] 位置开始添加字符串 "abcd" 的前 [2]~[2+(3-1)] 个字符，并返回形成的新字符串
    return 0;
}