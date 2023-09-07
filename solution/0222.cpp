#include "../include/help.h"

// 二叉树数的深度, 多用c++新特性更好
class Solution1 {
  int traversal(TreeNode *node) {
    if (node == nullptr)
      return 0;
    int left_num = traversal(node->left);
    int right_num = traversal(node->right);
    return left_num + right_num + 1;
  }

public:
  int countNodes(TreeNode *root) {
    int res = 0;
    res = std::move(traversal(root));
    return res;
  }
};

class Solution2 {
  int traversal(TreeNode *node) {
    if (node == nullptr)
      return 0;
    return traversal(node->left) + traversal(node->right) + 1;
  }

public:
  int countNodes(TreeNode *root) {
    int res = 0;
    res = std::move(traversal(root));
    return res;
  }
};
// 利用完全二叉树的特性来解决这个问题
class Solution3 {
public:
  int traversal(TreeNode *node) {
    if (node == nullptr)
      return 0;

    TreeNode *left = node->left;
    TreeNode *right = node->right;
    int left_depth = 0, right_depth = 0;
    while (left) {
      left = left->left;
      left_depth++;
    }
    while (right) {
      right = right->right;
      right_depth++;
    }

    // 检验是否为满二叉树, 满二叉树
    if (left_depth == right_depth) {
      return (2 << left_depth) - 1;
    }
    return traversal(node->left) + traversal(node->right) + 1;
  }

  int countNodes(TreeNode *root) {
    int res = 0;
    res = std::move(traversal(root));
    return res;
  }
};