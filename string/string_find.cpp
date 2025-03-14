#include "../include/help.h"


int main()
{
    string str;
    cin >> str;

    str.find("ab");//返回字符串 ab 在 str 的位置
    str.find("ab", 2);//在 str[2]~str[n-1] 范围内查找并返回字符串 ab 在 str 的位置
    str.rfind("ab", 2);//在 str[0]~str[2] 范围内查找并返回字符串 ab 在 str 的位置

    //first 系列函数
    str.find_first_of("apple");//返回 apple 中任何一个字符首次在 str 中出现的位置
    str.find_first_of("apple", 2);//返回 apple 中任何一个字符首次在 str[2]~str[n-1] 范围中出现的位置
    str.find_first_not_of("apple");//返回除 apple 以外的任何一个字符在 str 中首次出现的位置
    str.find_first_not_of("apple", 2);//返回除 apple 以外的任何一个字符在 str[2]~str[n-1] 范围中首次出现的位置

    //last 系列函数
    str.find_last_of("apple");//返回 apple 中任何一个字符最后一次在 str 中出现的位置
    str.find_last_of("apple", 2);//返回 apple 中任何一个字符最后一次在 str[0]~str[2] 范围中出现的位置
    str.find_last_not_of("apple");//返回除 apple 以外的任何一个字符在 str 中最后一次出现的位置
    str.find_last_not_of("apple", 2);//返回除 apple 以外的任何一个字符在 str[0]~str[2] 范围中最后一次出现的位置

    //以上函数如果没有找到，均返回string::npos
    cout << string::npos;
    return 0;
}

