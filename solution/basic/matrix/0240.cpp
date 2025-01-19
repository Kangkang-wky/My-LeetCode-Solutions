#include "../include/help.h"

/**
 * @brief 搜索 target 矩阵, 搜索 target 部分, 将其作为最后结果
 *        matrix 矩阵
 */

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int i = matrix.size() - 1, j = 0;
        while(i >= 0 && j < matrix[0].size()){
            if (matrix[i][j] > target)  i--;
            else if (matrix[i][j] < target) j++;
            else return true;
        }
        return false;
    }
};