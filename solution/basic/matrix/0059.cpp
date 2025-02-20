#include "../include/help.h"

class Solution1 {
private:
    static constexpr int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n, vector<int>(n, 0));

        int row = 0, column = 0, dir_index = 0;

        for (int i = 1; i <= n * n; i++) {  
            res[row][column] = i;
            
            int nextstep_row = row + dir[dir_index][0];
            int nextstep_column = column + dir[dir_index][1];

            if (nextstep_row < 0 || nextstep_row >= n || 
                nextstep_column < 0 || nextstep_column >= n || 
                res[nextstep_row][nextstep_column] != 0) {
                    dir_index = (dir_index + 1) % 4;
            }
            row = row + dir[dir_index][0];
            column = column + dir[dir_index][1];

        }
        return res;
    }
};


class Solution2 {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector <int> res;
        if(matrix.empty()) return res; //若数组为空，直接返回答案
        int up = 0; //赋值上下左右边界
        int down = matrix.size() - 1;
        int left = 0;
        int right = matrix[0].size() - 1;
        while(true)
        {   
            // 按照四个方向分别进行遍历即可
            for(int i = left; i <= right; ++i) res.push_back(matrix[up][i]); //向右移动直到最右
            ++up;
            if(++up > down) break;      //重新设定上边界，若上边界大于下边界，则遍历遍历完成，下同

            for(int i = up; i <= down; ++i) res.push_back(matrix[i][right]); //向下
            --right;
            if(--right < left) break;   //重新设定有边界
            
            for(int i = right; i >= left; --i) res.push_back(matrix[down][i]); //向左
            --down;
            if(--down < up) break;      //重新设定下边界
            
            for(int i = down; i >= up; --i) res.push_back(matrix[i][left]); //向上
            ++left;
            if(++left > right) break;   //重新设定左边界
        }
        return res;
    }
};