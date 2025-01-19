#include "../include/help.h"

class Solution {
private:
  bool dfs(TreeNode *root, long long left_node, long long right_node) {
    if (root == nullptr) {
      return true;
    }
    if (root->val <= left_node || root->val >= right_node) {
      return false;
    }
    return dfs(root->left, left_node, root->val) &&
           dfs(root->right, root->val, right_node);
  }

public:
  bool isValidBST(TreeNode *root) {
    if (root->left == nullptr && root->right == nullptr) {
      return true;
    } else {
      return dfs(root, LONG_MIN, LONG_MAX);
    }
  }
};