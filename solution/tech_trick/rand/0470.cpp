#include "../include/help.h"

/**
 * @brief 使用 rand7 生成 rand10
 * 
 */


class Solution {
public:
    int rand10() {
        int num = numeric_limits<int>::max();
        while (num > 40) {
            num = (rand7() - 1) * 7 + rand7();
        }

        return (num - 1) % 10 + 1;
        
    }
};