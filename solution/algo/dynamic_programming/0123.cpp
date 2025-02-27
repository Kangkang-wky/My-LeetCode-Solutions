#include "../include/help.h"

/**
 * @brief 股票买卖的最佳时机 III
 * 
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(), vector<int>(5, 0));
        dp[0][1] = -prices[0];
        dp[0][3] = -prices[0];
        for(int i = 1; i < prices.size(); i++){
            dp[i][1] = max(dp[i - 1][1], -prices[i]);                   // dp[i][1] 表示第 i 天第一次持有股票
            dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);     // dp[i][2] 表示第 i 天第一次不持有股票
            dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);     // dp[i][3] 表示第 i 天第二次持有股票
            dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);     // dp[i][4] 表示第 i 天第二次不持有股票
        }
        return dp[prices.size() - 1][4];
    }
};