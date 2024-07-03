#include "../include/help.h"

class Solution {
public:
  // 三数之和
  vector<vector<int>> threeSum(vector<int> &nums) {
    vector<vector<int>> res;

    // 给数组进行排序
    sort(nums.begin(), nums.end());

    // 固定 k 的位置, 然后逐步移动 k, 然后 i, j 分别从
    // [k, len(nums) - 1] 处分别移动

    for (int k = 0; k < nums.size() - 2; k++) {
      // > 0 不可能有符合条件的数值
      if (nums[k] > 0) {
        break;
      }

      // 这个地方有问题, 暂时先不纠结了
      if (k > 0 & nums[k] == nums[k - 1]) {
        continue;
      }

      int i = k + 1, j = nums.size() - 1;

      while (i < j) {
        int sum = nums[k] + nums[i] + nums[j];

        if (sum > 0) {
          j--;

          while (i < j && nums[j] == nums[j + 1]) {
            j--;
          }

        } else if (sum < 0) {
          i++;

          while (i < j && nums[i] == nums[i - 1]) {
            i++;
          }

        } else {
          vector<int> temp{k, i, j};
          res.emplace_back(temp);
          i++;
          j--;

          while (i < j && nums[j] == nums[j + 1]) {
            j--;
          }

          while (i < j && nums[i] == nums[i - 1]) {
            i++;
          }
        }
      }
    }
    return res;
  }
};