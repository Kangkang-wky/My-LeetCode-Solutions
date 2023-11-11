#include "../include/help.h"

class Solution {
public:
  vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2) {
    vector<int> result(nums1.size(), -1);
    unordered_map<int, int> hashmap;
    stack<std::pair<int, int>> st;

    // hash 映射, nums1 nums2 没有重复元素, 因此将 nums2 中的值(nums1 中有的)
    // 映射为 nums1 的索引 为results 数组做准备
    for (size_t i = 0; i < nums1.size(); i++) {
      hashmap[nums1[i]] = i;
    }

    // 单调栈, 栈底自栈顶递减
    for (size_t i = 0; i < nums2.size(); i++) {
      if (st.empty()) {
        st.push(make_pair(i, nums2[i]));
      }
      // 栈不为空
      else {
        // 栈顶元素大于等于当前的 nums[i]
        if (nums2[i] <= st.top().second) {
          st.push(make_pair(i, nums2[i]));
        }
        // 栈顶元素小于当前的 nums[i] 找到更大的了，
        else {
          while (!st.empty() && nums2[i] > st.top().second) {
            // 看是否在 num1 中存在
            if (hashmap.count(st.top().second)) {
              // 通过 hashmap 访问到其在 nums1 的位置
              result[hashmap[st.top().second]] = nums2[i];
            }
            st.pop();
          }
          st.push(make_pair(i, nums2[i]));
        }
      }
    }
    return result;
  }
};