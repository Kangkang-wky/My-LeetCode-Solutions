#include "../include/help.h"

/**
 * @brief 全排列
 * 
 */

class Solution {
private:
  vector<bool> visit_num;
  vector<vector<int>> res;
  vector<int> tmp;

public:
  // dfs 方式吧
  // dfs 深度
  void dfs(vector<int> &nums, int k) {

    if (k == nums.size()) {
      return;
    }
    for (int i = 0; i < nums.size(); i++) {
      if (visit_num[i] == false) {
        // 做完
        tmp.push_back(nums[i]);
        visit_num[i] = true;

        if (k == (nums.size() - 1)) {
          res.push_back(tmp);
        }

        dfs(nums, k + 1);

        // 回溯, 还原
        tmp.pop_back();
        visit_num[i] = false;
      }
    }
  }
  vector<vector<int>> permute(vector<int> &nums) {
    visit_num.resize(nums.size(), false);
    dfs(nums, 0);
    return res;
  }
};