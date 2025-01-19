#include "../include/help.h"

class Solution {
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