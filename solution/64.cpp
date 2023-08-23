class Solution {
public:
  int minPathSum(vector<vector<int>> &grid) {
    // dp 问题
    // 要求和最小
    // dp[i][j] 表示 第 i  j 个小方块的路径和最小
    // 递推公式  dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j] (i =\ 0, j
    // =\ 0)
    //            dp[0][j] = dp[0][j-1] + grid[i][j];    (i == 0)
    //            dp[i][0] = dp[i-1][0] + grid[i][j];    (j == 0)
    // dp 初始化 dp[0][0] = grid[0][0]

    int m = grid.size();
    int n = grid[0].size();
    auto dp = vector<vector<int>>(m, vector<int>(n));
    dp[0][0] = grid[0][0];
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (i != 0 && j != 0)
          dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        else if (i == 0 && j != 0)
          dp[0][j] = dp[0][j - 1] + grid[i][j];
        else if (i != 0 && j == 0)
          dp[i][0] = dp[i - 1][0] + grid[i][j];
      }
    }
    return dp[m - 1][n - 1];
  }
};