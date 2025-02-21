#include "../include/help.h"

/**
 * @brief 最长递增子序列
 *        dp[i] 其中表示以 i 结尾的子序列的长度
 *        dp[i] = max(dp[i], dp[j] + 1) if nums[i] > dp[j]
 *        // Todo: 
 */

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();

        // 首先将 dp 数组都初始化为 1
        vector<int> dp(n, 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) {
                    dp[i] = std::max(dp[i], dp[j] + 1); // 递推公式
                }
            }
        }
        int res = numeric_limits<int>::min();
        for (int i = 0; i < n; i++) {
            res = std::max(res, dp[i]);
        }
        return res;
    }
};