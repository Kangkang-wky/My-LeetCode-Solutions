#include "../include/help.h"

// 题目中要求在二叉搜索树上任意两节点的差的绝对值的最小值。

// 注意是二叉搜索树是有序的。

// 遇到在二叉搜索树最值、差值等价于有序数组最值、差值

// 第一种做法直接输出到数组

class Solution1 {
public:
  void dfs(vector<int> &num, TreeNode *node) {
    if (node == nullptr) {
      return;
    }
    dfs(num, node->left);
    num.emplace_back(node->val);
    dfs(num, node->right);
  }
  int getMinimumDifference(TreeNode *root) {
    vector<int> num;
    int min_num = numeric_limits<int>::max();
    dfs(num, root);
    for (size_t i = 0; i < num.size() - 1; i++) {
      min_num = std::min(min_num, num[i + 1] - num[i]);
    }
    return min_num;
  }
};

// 第二种做法是直接用一个节点来记录前驱以及后继

class Solution2 {
private:
  TreeNode *pre = nullptr;
  int min_num = numeric_limits<int>::max();

public:
  void dfs(TreeNode *node) {
    if (node == nullptr) {
      return;
    }
    dfs(node->left);
    // 防御性编程
    if (pre != nullptr) {
      min_num = std::min(min_num, node->val - pre->val);
    }
    pre = node;
    dfs(node->right);
  }
  int getMinimumDifference(TreeNode *root) {
    dfs(root);
    return min_num;
  }
};