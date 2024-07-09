#include "../include/help.h"

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

class Solution {
public:
  // 排序问题
  int leastInterval(vector<char> &tasks, int n) {

    int length = tasks.size();

    vector<int> alpha_hashmap(26, 0);

    // 统计出所有的字符的出现情况
    for (auto &alpha : tasks) {
      alpha_hashmap[alpha - 'A']++;
    }
    // 最大的排第一个
    sort(alpha_hashmap.begin(), alpha_hashmap.end(),
         [](int &x, int &y) { return x > y; });

    // 完成以上排序, 得到最大的字符即可
    int max_size = alpha_hashmap[0];
    int lastline_element = 0;

    std::for_each(alpha_hashmap.begin(), alpha_hashmap.end(),
                  [&lastline_element, max_size](const auto &element) {
                    if (element == max_size) {
                      lastline_element++;
                    }
                  });

    // 如果 n 比较大, 能容纳下其他字符
    // 如果 n 比较小, 不能容纳其他字符, 即字符数量说明了实际的数量

    return max((max_size - 1) * (n + 1) + lastline_element, length);
  }
};