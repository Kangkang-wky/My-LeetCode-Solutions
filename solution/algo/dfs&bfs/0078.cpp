#include "../include/help.h"

class Solution {
public:
    void dfs(int iter, vector<int>&nums, vector<int>&temp, vector<vector<int>> &res) {
        // iter 选择
        if (iter == nums.size()) {
            res.push_back(temp);
            return;
        }

        // 选择
        temp.push_back(nums[iter]);
        dfs(iter + 1, nums, temp, res);
        temp.pop_back();
        
        // 不选
        dfs(iter + 1, nums, temp, res);
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        std::vector<vector<int>> results;
        std::vector<int> temp;
        dfs(0, nums, temp, results);
        return results;
    }
};