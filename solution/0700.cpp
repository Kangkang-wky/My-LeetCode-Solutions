#include "../include/help.h"

class Solution {
public:
  TreeNode *searchBST(TreeNode *root, int val) {
    if (root == nullptr)
      return NULL;
    int _val = root->val;
    if (val == _val) {
      return root;
    }
    TreeNode *res = nullptr;
    if (val < _val) {
      res = searchBST(root->left, val);
    } else {
      res = searchBST(root->right, val);
    }
    return res;
  }
};