#include "../include/help.h"

// 单调栈, 循环数组
// 所谓单调栈, 栈中存在的数字都是还没有找到对应元素的
// 通过继续访问数组, 来将栈中的信息逐一确定
class Solution {
public:
  vector<int> nextGreaterElements(vector<int> &nums) {
    vector<int> result(nums.size(), -1);
    stack<std::pair<int, int>> st;

    // 单调栈, 栈底自栈顶递减
    for (size_t i = 0; i < nums.size() * 2; i++) {
      size_t mod = nums.size();
      if (st.empty()) {
        st.push(make_pair(i % mod, nums[i % mod]));
      }
      // 栈不为空
      else {
        // 栈顶元素大于等于当前的 nums[i]
        if (nums[i % mod] <= st.top().second) {
          st.push(make_pair(i, nums[i % mod]));
        }
        // 栈顶元素小于当前的 nums[i] 找到更大的了，
        else {
          while (!st.empty() && nums[i % mod] > st.top().second) {
            result[st.top().first % mod] = nums[i % mod];
            st.pop();
          }
        }
        st.push(make_pair(i, nums[i % mod]));
      }
    }
    return result;
  }
};