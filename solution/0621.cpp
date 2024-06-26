#include "../include/help.h"

class Solution {
public:
    // 排序问题
    int leastInterval(vector<char>& tasks, int n) {
        int length = tasks.size();
        vector<int> alpha_hashmap(26, 0);
        
        // 统计一下数量
        for (auto &alpha : tasks)  alpha_hashmap[alpha - 'A']++;

        // 简单的 lambda 函数
        sort(alpha_hashmap.begin(), alpha_hashmap.end(), [] (int &x, int &y) { x > y; });


    }

    // 按照桶排序的方式即可
    // 先排最大的出现次数最多的, 这样一定能放下, 比如间隔是 3 的话
    // A B x x 
    // A B x x
    // A B x x
    // A B x x
    // A

    // 这样计算至少有 (max_size - 1) x (n + 1) + last_line_element 
    // 这样做再加上 
    // 另外一种情况, 冷却时间很短, 但是任务种类很多的时候
    // 即使 tasks.size() 大小
};