#include "../include/help.h"


/**
 * @brief 有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。

// 例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
// 给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP 地址，这些地址可以通过在 s 中插入 '.' 来形成。
// 你 不能 重新排序或删除 s 中的任何数字。你可以按 任何 顺序返回答案。
 * 
 */

/**
 * @brief 复原 IP 地址, 分割原来得 IP 地址字符串, 从而判断其中的 num 是否位于合法区间
 * 
 */

class Solution {
private: 
    bool check_num(string num) {
        int sum = 0;
        for (int i = 0; i < num.size(); i++) {
            sum = sum * 10 + num[i] - '0';
        }
        if (sum > 255) {
            return false;
        }
        if (num[0] == '0' && num.size() > 1) {
            return false;
        }
        return true;
    }

public:
    vector<string> restoreIpAddresses(string s) {
        
        vector<string> res;
        int n = s.size();

        if (n < 4 || n > 12)    return res;

        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n - 1; j++) {
                for (int k = j + 1; k < n - 1; k++) {
                    string num1 = s.substr(0, i - 0 + 1);
                    string num2 = s.substr(i + 1, j - (i + 1) + 1);
                    string num3 = s.substr(j + 1, k - (j + 1) + 1);
                    string num4 = s.substr(k + 1, (n - 1) - (k + 1) + 1);
                    
                    if (check_num(num1) && check_num(num2) && check_num(num3) && check_num(num4)) {
                        res.emplace_back(num1 + "." + num2 + "." + num3 + "." + num4);
                    }
                }
            }
        }
        return res;
    }
};