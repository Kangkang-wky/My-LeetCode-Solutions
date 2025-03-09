#include "../include/help.h"

/**
 * @brief dp 问题可以分为背包问题和序列问题
 *           矩阵动态规划, 字符串匹配动态规划
 * 
 */

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        
        // 初始化 dp 数组 
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // 需要注意这里处理 dp 数组初始化的细节
        // 处理好循环顺序, 并设置成 dp[0][1] = 1

        dp[0][1] = 1;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (obstacleGrid[i][j] == 0) {
                    dp[i + 1][j + 1] = dp[i][j + 1] + dp[i + 1][j];
                }
            }
        }
        return dp[m][n];            
    }
};