#include "../include/help.h"

/*
   本题需要注意的是如何做去重操作
   TODO：看 沉思录 中两种去重操作
*/

class Solution {
  vector<bool> visit;

public:
  void dfs(vector<int> &nums, int index, vector<int> &permute,
           vector<vector<int>> &res) {
    if (index == nums.size()) {
      res.emplace_back(permute);
      return;
    }
    for (int i = 0; i < nums.size(); i++) {
      if (visit[i] || (i > 0 && nums[i] == nums[i - 1] && !visit[i - 1])) {
        // visit[i] == 1 跳过
        // 重复数字  1 2 2 2 3
        // 前两个条件保证重复数字，第三个条件保证之前的重复的数字如果没有填入，之后的数字也不会填入，保证其是按照从左到右的顺序依次填入的
        continue;
      }
      // 需要填入数字的情况  do undo
      visit[i] = true;
      permute.emplace_back(nums[i]);
      dfs(nums, index + 1, permute, res);
      permute.pop_back();
      visit[i] = false;
    }
  }

  vector<vector<int>> permuteUnique(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> permute;
    sort(nums.begin(), nums.end());
    visit.resize(nums.size());
    fill(visit.begin(), visit.end(), false);
    dfs(nums, 0, permute, res);
    return res;
  }
};
