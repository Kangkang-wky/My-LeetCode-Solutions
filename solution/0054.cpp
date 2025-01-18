#include "../include/help.h"

/**
 * @brief 写个模拟即可, 完成螺旋矩阵的操作
 * 
 */



class Solution {
private:
    // 顺时针的四个方向, 向右, 向下, 向左, 向上
    static constexpr int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }


        int m = matrix.size();
        int n = matrix[0].size();
        int row = 0;
        int column = 0;
        
        vector<int> res{};
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        int direction_index = 0;

        for(int i = 0; i < m * n; i++) {
            res.emplace_back(matrix[row][column]);
            visited[row][column] = true;
            
            int nextstep_row = row + directions[direction_index][0];
            int nextstep_column = column + directions[direction_index][1];

            // 碰壁了, 开始顺时针拐弯
            if (nextstep_row < 0 || nextstep_row >= m || nextstep_column < 0 || nextstep_column >= n || visited[nextstep_row][nextstep_column] == true) {
                direction_index = (direction_index + 1) % 4;
            }

            row += directions[direction_index][0];
            column += directions[direction_index][1];
    
        }
        return res;
    }
};