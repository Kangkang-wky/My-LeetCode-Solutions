#include "../include/help.h"

// 使用 visit 数组进行层内去重
class Solution {
  vector<bool> visit;

private:
  // dfs (1) dfs function 参数
  void dfs(vector<int> &candidates, int target, int Startindex, int sum,
           vector<vector<int>> &res, vector<int> &arr) {
    // dfs (2) 搜索的终止条件
    if (sum == target) {
      res.emplace_back(arr);
      return;
    }
    // dfs (3) 搜索的遍历顺序
    // 剪枝 (1) 相加的和要大于 target   (2) 此处从 Startindex 处开始因为
    // 顺序排序之前的已经用过了
    for (int i = Startindex;
         i < candidates.size() && candidates[i] + sum <= target; i++) {
      // 剪枝 (3) 层间剪枝  当层间有重复的数字的时候
      if (i > 0 && candidates[i] == candidates[i - 1] &&
          visit[i - 1] == false) {
        continue;
      }
      visit[i] = true;
      arr.emplace_back(candidates[i]);
      sum += candidates[i];
      dfs(candidates, target, i + 1, sum, res, arr);
      sum -= candidates[i];
      arr.pop_back();
      visit[i] = false;
    }
  }

public:
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    vector<vector<int>> res;
    vector<int> arr;
    visit.resize(candidates.size());
    fill(visit.begin(), visit.end(), false);
    sort(candidates.begin(), candidates.end());
    dfs(candidates, target, 0, 0, res, arr);
    return res;
  }
};

// 不使用 visit 数组

// 不使用 visit 数组
class Solution2 {
private:
  // dfs (1) dfs function 参数
  void dfs(vector<int> &candidates, int target, int Startindex, int sum,
           vector<vector<int>> &res, vector<int> &arr) {
    // dfs (2) 搜索的终止条件
    if (sum == target) {
      res.emplace_back(arr);
      return;
    }
    // dfs (3) 搜索的遍历顺序
    // 剪枝 (1) 相加的和要大于 target   (2) 此处从 Startindex 处开始因为
    // 顺序排序之前的已经用过了
    for (int i = Startindex;
         i < candidates.size() && candidates[i] + sum <= target; i++) {
      // 剪枝 (3) 层间剪枝  当层间有重复的数字的时候
      // 这个其实就是在 树层上进行剪枝，减去相同的数
      if (i > Startindex && candidates[i] == candidates[i - 1]) {
        continue;
      }
      arr.emplace_back(candidates[i]);
      sum += candidates[i];
      dfs(candidates, target, i + 1, sum, res, arr); // 搜索到树的下一层
      sum -= candidates[i];
      arr.pop_back();
    }
  }

public:
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
    vector<vector<int>> res;
    vector<int> arr;
    sort(candidates.begin(), candidates.end());
    dfs(candidates, target, 0, 0, res, arr);
    return res;
  }
};
