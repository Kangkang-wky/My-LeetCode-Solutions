#include "../include/help.h"

// 递归写法

class Solution1 {
public:
  TreeNode *insertIntoBST(TreeNode *root, int val) {
    if (root == nullptr) {
      TreeNode *node = new TreeNode(val);
      return node;
    }
    if (root->val > val)
      root->left = insertIntoBST(root->left, val);
    if (root->val < val)
      root->right = insertIntoBST(root->right, val);
    return root;
  }
};

// 递归写法，个人之前习惯的递归函数无返回值

class Solution2 {
private:
  // 注意使用函数参数为引用改变插入的值
  void travel(TreeNode *&cur, int val) {
    if (cur == nullptr) {
      cur = new TreeNode(val);
      return;
    }
    if (cur->val > val)
      travel(cur->left, val);
    else
      travel(cur->right, val);
    return;
  }

public:
  TreeNode *insertIntoBST(TreeNode *root, int val) {
    travel(root, val);
    return root;
  }
};