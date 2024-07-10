#include "../include/help.h"

// 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k
// 高的元素。你可以按 任意顺序 返回答案。

class Solution {
public:
  vector<int> topKFrequent(vector<int> &nums, int k) {
    std::unordered_map<int, int> hashmap;

    for (const auto &num : nums) {
      hashmap[num]++;
    }
    // 以上完成 hashmap 部分++

    using Mypair = std::pair<int, int>;

    // 提取到 vector 中即可
    std::vector<Mypair> sort_array(hashmap.begin(), hashmap.end());

    sort(sort_array.begin(), sort_array.end(),
         [](const Mypair &a, const Mypair &b) { return a.second > b.second; });

    std::vector<int> res;
    for (int i = 0; i < k; i++) {
      res.emplace_back(sort_array[i].first);
    }
    return res;
  }
};