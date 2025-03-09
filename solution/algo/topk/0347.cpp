#include "../include/help.h"

// 给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k
// 高的元素。你可以按 任意顺序 返回答案。

// 暴力排序 nlogn 复杂度
// 堆排序 nlogk 复杂度


/**
 * @brief 前 k 个高频元素, 先统计出现的次数, 再进行排序
 * 
 */

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

/**
 * @brief 哈希表 + 最小堆
 * 
 */


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> hashmap;
        for (auto& v : nums) {
            hashmap[v]++;
        }

        struct hashmap_cmp {
            bool operator()(const std::pair<int, int> &m, const std::pair<int, int> &n) const { 
              return m.second > n.second; 
            }
        };

        // pair 的第一个元素代表数组的值，第二个元素代表了该值出现的次数
        priority_queue<pair<int, int>, vector<pair<int, int>>, hashmap_cmp> q;
        for (auto& [num, count] : hashmap) {
            if (q.size() == k) {
                if (q.top().second < count) {
                    q.pop();
                    q.emplace(num, count);
                }
            } 
            else {
                q.emplace(num, count);
            }
        }
        vector<int> res;
        while (!q.empty()) {
            res.emplace_back(q.top().first);
            q.pop();
        }
        return res;
    }
};