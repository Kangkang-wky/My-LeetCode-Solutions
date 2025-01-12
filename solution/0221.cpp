#include "../include/help.h"

// 最大正方形
// 前缀和实现即可
// O(mn)
// 实现一个简单的前缀和访问序列即可
// 求解出 sum(i, j)

// 第二种解法是采用动态规划进行求解

class Solution1 {
public:

  bool check(int m, int n, int x, vector<vector<int>>& sum_array)
  {
      // 枚举符合条件的子矩阵
      for(int i = 1; i <= m - x; i++)
      {
          for(int j = 1; j <= n - x; j++)
          {
              int x1 = i, y1 = j;                   // 子矩阵的左上角
              int x2 = x1 + x, y2 = y1 + x;         // 子矩阵的右下角
              int t = sum_array[x2][y2] - sum_array[x1-1][y2] - sum_array[x2][y1 - 1] + sum_array[x1 - 1][y1 - 1]; // 子矩阵的前缀和
              if(t == x * x){                       // 找到即返回
                return true;
              }
          }
      }

      return false;
  }


  int maximalSquare(vector<vector<char>> &matrix) {
    int m = matrix.size();
    int n = matrix[0].size();

    // m * n 大小的数组初始化 // 矩阵大小是 (m + 1) * (n + 1)
    vector<vector<int>> sum(m + 1, vector<int>(n + 1, 0));

    // 第一列初始化
    // for (int i = 1; i <= m; i++) {
    //   if (matrix[i][0] == '1') {
    //     sum[i][0] = sum[i-1][0] + 1;
    //   }
    //   else {
    //     sum[i][0] = sum[i-1][0];
    //   }
    // }

    // // 第一行初始化
    // for (int j = 1; j < n; j++) {
    //   if (matrix[0][j] == '1') {
    //     sum[0][j] = sum[0][j-1] + 1;
    //   }
    //   else {
    //     sum[0][j] = sum[0][j-1];
    //   }
    // }
  
    // 行列使用上
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        if (matrix[i-1][j-1] == '1') {
          sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + 1;
        } 
        else{
          sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        }          
      }
    }

    int l = 0, r = min(m, n);

    // 二分不断测试最大正方形的边长
    while(l < r)
    {
        int mid = l + (r - l) / 2;
        if(check(m, n, mid, sum)) l = mid;
        else r = mid - 1;
    }

    return l * l;
  }
};



class Solution2 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m, vector<int>(n));  // dp[i][j]表示以(i, j)为正方形右下角构成的最大正方形的边长
        int max_res = 0;
        
        // 处理边界条件 首行元素和首列元素的最大边长取决于单元格本身是否为1
        for(int j = 0; j < n; j++){
            dp[0][j] = matrix[0][j] - '0';
            max_res = max(max_res, dp[0][j]);
        }
        
        for(int i = 0; i < m; i++){
            dp[i][0] = matrix[i][0] - '0';
            max_res = max(max_res, dp[i][0]);
        }
        // 状态转移
        for(int i = 1; i < m; i++){
            for(int j = 1; j < n; j++){
                if(matrix[i][j] == '0') {
                  continue;
                }
                dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
                max_res = max(max_res, dp[i][j]);
            }
        }
        return max_res * max_res;
    }
};