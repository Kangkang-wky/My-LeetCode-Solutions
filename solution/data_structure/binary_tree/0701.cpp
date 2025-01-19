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

// 迭代法插入部分
// 迭代法插入考虑中序遍历插入即可
class Solution3 {
public:
  TreeNode *insertIntoBST(TreeNode *root, int val) {

    // 如果 root 为空指针, 直接插入即可
    if (root == nullptr) {
      // 开辟一份地址空间
      TreeNode *node = new TreeNode(val);
      return node;
    }

    // node 进行二分查找即可
    TreeNode *node = root;     // root 不是 nullptr
    while (node->val != val) { // 相等表示找到了

      //
      if (node->val < val) {
        // assert
        if (node->right == nullptr) {
          // 找到插入即可
          node->right = new TreeNode(val);
        }
        node = node->right;
      } else {
        // assert
        if (node->left == nullptr) {
          // 找到插入即可
          node->left = new TreeNode(val);
        }
        node = node->left;
      }
    }
    return root;
  }
};