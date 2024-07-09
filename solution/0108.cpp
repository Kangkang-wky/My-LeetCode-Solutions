#include "../include/help.h"

// 通过中序遍历找到最优数组
// 将有序数组转为二叉树
class Solution {
public:
  TreeNode *sortedArrayToBST(vector<int> &nums) {
    if (nums.size() == 0) {
      return nullptr;
    }
    return dfs(nums, 0, nums.size() - 1);
  }

  TreeNode *dfs(vector<int> &nums, int left, int right) {

    // 终止条件
    if (left > right) {
      return nullptr;
    }

    // mid 找到 nums 的中位数,
    int mid = left + (right - left) / 2;

    // 当前节点
    int mid_node_value = nums[mid];
    TreeNode *node = new TreeNode(mid_node_value);

    node->left = dfs(nums, left, mid - 1);
    node->right = dfs(nums, mid + 1, right);

    return node;
  }
};