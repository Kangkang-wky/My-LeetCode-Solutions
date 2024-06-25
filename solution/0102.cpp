#include "../include/help.h"

class Solution {
public:
  vector<vector<int>> levelOrder(TreeNode *root) {
    // 逐层返回

    vector<vector<int>> level_order_tree;

    if (root == nullptr)
      return level_order_tree;

    queue<TreeNode *> tree_queue;
    tree_queue.push(root);

    int level = 0;
    while (!tree_queue.empty()) {

      // 返回我这一层需要多少个结点, 有多少个结点
      // 就做多少次 pop 操作
      int layer_node_size = tree_queue.size();
      vector<int> layer_node_val;

      // 头部
      for (size_t i = 0; i < layer_node_size; i++) {
        TreeNode *cur_node = tree_queue.front();
        tree_queue.pop();

        if (cur_node->left != nullptr) {
          tree_queue.push(cur_node->left);
        }
        if (cur_node->right != nullptr) {
          tree_queue.push(cur_node->right);
        }
        layer_node_val.push_back(cur_node->val);
        level++;
      }
      level_order_tree.push_back(layer_node_val);
    }

    return level_order_tree;
  }
};