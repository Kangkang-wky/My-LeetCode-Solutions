#include "../include/help.h"

// 前缀和 + hashmap 优化

// pre_sum[i] - pre_sum[j] = k
// pre_sum[j] = pre_sum[i] - k
// 从左往右更新  i 从 0 遍历到nums.size()
// 这样 更新 i 的时候已经保证 j 已经更新了, 通过这样的方式 前缀和差的正常更新

class Solution1 {
public:
  int subarraySum(vector<int> &nums, int k) {
    // 使用 unordered_map 来维护前缀和
    unordered_map<int, int> hashmap;
    // 前缀和为 0 的有一个
    hashmap[0] = 1;
    int res = 0, pre_sum = 0;
    for (auto &x : nums) {
      // 前缀和求解
      pre_sum += x;
      if (hashmap.find(pre_sum - k) != hashmap.end()) {
        res += hashmap[pre_sum - k];
      }
      hashmap[pre_sum]++;
    }
    return res;
  }
};

// 前缀和，但是该前缀和会超时

class Solution2 {
public:
  int subarraySum(vector<int> &nums, int k) {
    int count = 0;
    for (int start = 0; start < nums.size(); ++start) {
      int sum = 0;
      for (int end = start; end >= 0; --end) {
        sum += nums[end];
        if (sum == k) {
          count++;
        }
      }
    }
    return count;
  }
};