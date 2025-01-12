#include "../include/help.h"

// 给你一个含 n 个整数的数组 nums ，其中 nums[i] 在区间 [1, n] 内。
// 请你找出所有在 [1, n] 范围内但没有出现在 nums 中的数字，并以数组的形式返回结果。

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        vector<bool> hash(n + 1, false);
        vector<int> res;
        for (auto &num : nums) {
            hash[num] = true;
        }
        for (int i = 1; i <=n ; i++) {
            if (hash[i] == false) {
                res.emplace_back(i);
            }
        }
        return res;
    }
};