#include "../include/help.h"

// 贪心问题

class Solution {
private:
  // 前后拼接, 字典序更大的排在前面
  static bool cmp(int left, int right) {
    string string_L = to_string(left);
    string string_R = to_string(right);
    return string_L + string_R > string_R + string_L;
  }

public:
  string largestNumber(vector<int> &nums) {

    sort(nums.begin(), nums.end(), cmp);

    // 错误, 注意添加边界情况的处理
    if (nums[0] == 0) {
      return "0";
    }

    string res;
    for (int i = 0; i < nums.size(); i++) {
      res += to_string(nums[i]);
    }
    return res;
  }
};