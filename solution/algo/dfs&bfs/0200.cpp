#include "../include/help.h"

// dfs 即可
class Solution {
private:
  // 找迷宫四个方向, x, y 的变化, 依据上下左右的位置
  int dir[4][2] = {0, 1, 0, -1, -1, 0, 1, 0};
  void dfs(vector<vector<char>> &grid, vector<vector<bool>> &vis, int x,
           int y) {

    // 终止条件
    // 当前点是 (x, y)
    // 遍历寻找
    // dfs 向 4 个方向移动
    int n = grid.size();
    int m = grid[0].size();

    for (int i = 0; i < 4; i++) {
      int next_x = x + dir[i][0];
      int next_y = y + dir[i][1];

      if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= m) {
        continue;
      }
      if (!vis[next_x][next_y] && grid[next_x][next_y] == '1') {
        vis[next_x][next_y] = true;
        dfs(grid, vis, next_x, next_y);
      }
    }
  }

public:
  int numIslands(vector<vector<char>> &grid) {
    // 一个记录访问的数组
    // visist
    int n = grid.size();    // n 是 行
    int m = grid[0].size(); // m 是 列
    int res = 0;

    vector<vector<bool>> vis = vector<vector<bool>>(n, vector<bool>(m, false));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (vis[i][j] == false && grid[i][j] == '1') {
          res++;
          dfs(grid, vis, i, j);
        }
      }
    }

    return res;
  }
};