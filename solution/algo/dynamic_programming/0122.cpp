#include "../include/help.h"

// 需要特别注意 prices[i] 的值

/**
 * @brief 股票买卖的最佳时机 II
 *        dp[i][0] 表示第 i 天不持有股票
 *        dp[i][1] 表示第 i 天持有股票
 *
 */



class Solution {
public:
  int maxProfit(vector<int> &prices) {
    int n = prices.size();

    vector<vector<int>> dp(n, vector<int>(2, 0));
    dp[0][0] = 0, dp[0][1] = -prices[0];
    for (int i = 1; i < n; ++i) {
      dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
      dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    }
    return dp[n - 1][0];
  }
};