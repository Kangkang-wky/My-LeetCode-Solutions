#include "../include/help.h"

/**
 * @brief 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。
 *        数组中的每个元素代表你在该位置可以跳跃的最大长度。
 *        判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
 * 
 */

// dp 0
// dp[i] 表示 dp[i] 处是否能够到达
// dp 数组实现
// dp[i] = dp[j] (j 从 0 到 i - 1),  if(dp[j] == true 且 dp[j] >= i - j) 只要有一个满足就行




class Solution1 {
public:
    bool canJump(vector<int>& nums) {
        vector<bool> dp(nums.size(), false);
        
        dp[0] = true;
        for (int i = 1; i < nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] == true && i - j <= nums[j]) {  // 第 j 为 true, 且能到达 i
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[nums.size() - 1];
    }
};

class Solution2 {
public:
    bool canJump(vector<int>& nums) {
        int k = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (i > k) return false;
            k = max(k, i + nums[i]);
        }
        return true;
    }
};
