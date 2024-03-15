#include "../include/help.h"

class Solution {
private:
  void bfs(TreeNode *root, vector<double> &avg_vec) {
    queue<TreeNode *> my_que;
    my_que.push(root);
    while (!my_que.empty()) {

      int level_size = my_que.size();
      int64_t value = 0;
      for (int i = 0; i < level_size; i++) {
        TreeNode *tmp = my_que.front();
        my_que.pop();
        if (tmp->left != nullptr) {
          my_que.push(tmp->left);
        }
        if (tmp->right != nullptr) {
          my_que.push(tmp->right);
        }
        value += tmp->val;
      }
      avg_vec.emplace_back(static_cast<double>(value) / level_size);
    }
  }

public:
  vector<double> averageOfLevels(TreeNode *root) {
    vector<double> avg_vec;
    if (root == nullptr) {
      return avg_vec;
    } else {
      bfs(root, avg_vec);
      return avg_vec;
    }
  }
};