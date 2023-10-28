#include "../include/help.h"

// 构造最大二叉树
// 递归地在最大值左边的子数组前缀上 构建左子树
// 递归地在最大值右边的子数组后缀上 构建右子树
// TODO 有时间改成一版用
class Solution1 {
public:
  // 确定递归函数参数以及返回值
  TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
    // 确定终止条件, 当前数组只有一个值
    TreeNode *node = new TreeNode(0);
    if (nums.size() == 1) {
      node->val = nums[0];
      return node; // 退出循环
    }
    size_t max_index = 0;
    int max_num = 0;
    for (size_t i = 0; i < nums.size(); i++) {
      if (max_num < nums[i]) {
        max_num = nums[i];
        max_index = i;
      }
    }
    node->val = max_num;
    // 将左边放入左子树递归
    if (max_index > 0) {
      vector<int> left_nums(nums.begin(), nums.begin() + max_index);
      node->left = constructMaximumBinaryTree(left_nums);
    }
    // 将右边放入右子树递归
    if (max_index < (nums.size() - 1)) {
      vector<int> right_nums(nums.begin() + max_index + 1, nums.end());
      node->right = constructMaximumBinaryTree(right_nums);
    }
    return node;
  }
};
// 与中序后序遍历求二叉树建树写法类似
class Solution2 {
private:
  // 确定递归需要的返回值以及函数参数
  TreeNode *dfs(const vector<int> &nums, int left, int right) {
    // 确认终止条件
    if (left > right) {
      return nullptr;
    }
    // 找最大的数的 index, 处理单层逻辑
    size_t max_index = left;
    int max_num = nums[max_index];
    for (size_t i = left; i <= right; i++) {
      if (max_num < nums[i]) {
        max_num = nums[i];
        max_index = i;
      }
    }
    TreeNode *node = new TreeNode(max_num);
    node->left = dfs(nums, left, max_index - 1);
    node->right = dfs(nums, max_index + 1, right);

    return node;
  }

public:
  TreeNode *constructMaximumBinaryTree(vector<int> &nums) {
    TreeNode *root = dfs(nums, 0, nums.size() - 1);
    return root;
  }
};