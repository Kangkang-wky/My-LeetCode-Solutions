// 由于要求是乘积最大子数组
// 同时正负属性有要求, 因此

// 考虑实现两个数组的大小, 考虑以dp[i] 为最后一个数字的最小数与最大数
// 考虑实际情况, 假设是  -2 1 这种情况如何更新 dp_max
//                     -2 -1
//                     2  1
//                      2 -1
// dp_max[i] = max(dp_max[i - 1] * nums[i], max(dp_min[i - 1] * nums[i],
// nums[i])); dp_min[i] = min(dp_min[i - 1] * nums[i], min(dp_max[i - 1] *
// nums[i], nums[i]));
//
#include "../include/help.h"

class Solution {
public:
  int maxProduct(vector<int> &nums) {

    // 初始化的时候拷贝即可, 注意 dp_max[0] 与 dp_min[0] 的值即可
    vector<int> dp_max(nums);
    vector<int> dp_min(nums);

    for (int i = 1; i < nums.size(); i++) {
      dp_max[i] =
          max(dp_max[i - 1] * nums[i], max(dp_min[i - 1] * nums[i], nums[i]));
      dp_min[i] =
          min(dp_min[i - 1] * nums[i], min(dp_max[i - 1] * nums[i], nums[i]));
    }
    int res = *max_element(dp_max.begin(), dp_max.end());
    return res;
  }
};