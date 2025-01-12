#include "../include/help.h"

// 给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，
// 找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。
// 你可以按 任意顺序 返回这些组合。candidates 中的 同一个 数字可以 无限制重复被选取。
// 如果至少一个数字的被选数量不同，则两种组合是不同的。 对于给定的输入，保证和为 target 的不同组合数少于 150 个。


// 背包解法
// 无限背包即可
// 

// dfs 剪枝 回溯

class Solution {
private:
    void dfs(int idx, vector<int>& candidates, int target, vector<vector<int>>& ans, vector<int>& temp) {
        if (idx == candidates.size()) { // 达到 idx 的最大值即可 return
            return;
        }
        
        if (target == 0) {              // 达到和最小的时候 emplace_back 即可
            ans.emplace_back(temp);
            return;
        }

        // 直接跳过, 跳到下一个数的 dfs 部分
        dfs(idx + 1, candidates, target, ans, temp);
        
        // 选择当前数
        if (target - candidates[idx] >= 0) {
            temp.emplace_back(candidates[idx]);
            dfs(idx, candidates, target - candidates[idx], ans, temp);
            temp.pop_back();
        }
    }

public:

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> temp;
        dfs(0, candidates, target, res, temp);
        return res;
    }
};