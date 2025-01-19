#include "../include/help.h"

// 硬币兑换, 背包问题求解即可
// coins 使用, 要求凑出 amount 大小的背包即可
// 要求 coins 数量尽可能少
// coins 用不完

// 状态与状态转移方程

// dp[i] 表示凑够 i 大小的 背包需要的最少 coins 数量

// 初始化
// 其应该初始化为最大值
// dp[0] = 0;
// dp[lengh[coins.size()]] = 1;

// 状态转移方程
// 选择 x 需要遍历的范围是
// dp[i] = min(dp[i - x] + 1, dp[i]);

// 循环遍历

// 剪枝, 减少搜索空间

class Solution {
public:
  int coinChange(vector<int> &coins, int amount) {

    // 初始化为最大即可
    // 最大值设置不能为int 类型最大值这里, + 1 会超过上限要求
    int MAX_NUM = amount + 1;

    vector<int> dp(amount + 1, MAX_NUM);
    dp[0] = 0;

    // 闭区间循环【0, amount】, 求解所有的 dp 数组
    for (int i = 0; i <= amount; i++) {
      // 对所有满足条件的 coins 进行求解
      for (int j = 0; j < coins.size(); j++) {
        // 防御性编程 + 剪枝
        if (coins[j] <= i) {
          dp[i] = min(dp[i], dp[i - coins[j]] + 1);
        }
      }
    }

    return dp[amount] == MAX_NUM ? -1 : dp[amount];
  }
};