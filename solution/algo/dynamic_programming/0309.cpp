#include "../include/help.h"

// 买卖股票的最佳时机(包含冷冻期)
// 天数(prices.size())
// 操作状态是 买入, 卖出, 冷冻期
// 设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）
// 卖出股票后，你无法在第二天买入股票(即冷冻期为 1 天)

// dp 数组
// dp[t][2] 标记当前状态是买入还是卖出 0 买入 1 卖出
// 赚到的钱

// 状态转移方程
// 0 表示当前状态是买入的状态(未持有股票的最大利润)
// 1 表示当前状态是卖出的状态(持有股票的最大利润)
// 当前状态来自于前一天的状态

// 状态机有两种
//
// 不做操作第 t 天, 做操作第 t 天
// 第 t 天的股票
// dp[t][0] = max(dp[t-1][0], dp[t-2][1] - price[t])
// dp[t][1] = max(dp[t-1][1], dp[t-1][0] + price[t])

// 初始化边界
//

class Solution {
public:
  int maxProfit(vector<int> &prices) {
    vector<vector<int>> dp(prices.size() + 1, vector<int>(2, 0));
    dp[1][0] = -prices[0];

    for (int i = 2; i <= prices.size(); i++) {
      /*
      dp[i][0] 第i天持有股票收益;
      dp[i][1] 第i天不持有股票收益;
      注意 prices 是从 0 开始的
       */
      dp[i][0] = max(dp[i - 1][0], dp[i - 2][1] - prices[i - 1]);
      dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i - 1]);
    }

    return dp[prices.size()][1];
  }
};