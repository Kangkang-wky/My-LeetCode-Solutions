#include "../include/help.h"

class Solution1 {
public:
  void rotate(vector<vector<int>> &matrix) {
    int n = matrix.size();
    auto matrix_rotate = matrix;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        matrix_rotate[j][n - i - 1] = matrix[i][j];
      }
    }
    matrix = matrix_rotate;
  }
};

// 旋转矩阵
// 如果是旋转90度, 相当于4个点互相交换位置,
// 因此可以改为一个就地操作

// 注意 n 为奇数 与 n 为偶数的区别, 注意它的奇偶关系

class Solution2 {
public:
  void rotate(vector<vector<int>> &matrix) {
    int n = matrix.size();
    auto matrix_rotate = matrix;
    for (int i = 0; i < n / 2; i++) {
      for (int j = 0; j < (n + 1) / 2; j++) {

        int temp = matrix[i][j];
        matrix[i][j] = matrix[n - j - 1][i];
        matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
        matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
        matrix[j][n - i - 1] = temp;

        // matrix[j][n - i - 1] = matrix[i][j];
        // matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
        // // matrix[n - j - 1][n - (n - i - 1) - 1] = matrix[n - i - 1][n - j -
        // // 1];
        // matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
        // // matrix[i][n - (n - j - 1) - 1] = matrix[n - j - 1][i];
        // matrix[i][j] = matrix[n - j - 1][i];
      }
    }
  }
};