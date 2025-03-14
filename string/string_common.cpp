#include "../include/help.h"

int main()
{
    string str = "catmouse";

    // swap 交换
    string str1 = "cat";
    string str2 = "mouse";
    str1.swap(str2);        //把 str1 与 str2 交换

    // add 添加
    str.push_back('a');//在 str 末尾添加字符'a'
    str.append("abc");//在 str 末尾添加字符串"abc"

    // others
    int n = 3;
    str.size();//返回字符串长度
    str.length();//返回字符串长度
    str.empty();//检查 str 是否为空，为空返回 1，否则返回 0
    char c = str[n];//存取 str 第 n + 1 个字符
    str.at(n);//存取 str 第 n + 1 个字符（如果溢出会抛出异常）


    return 0;
}