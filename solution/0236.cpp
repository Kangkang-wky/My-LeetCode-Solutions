#include "../include/help.h"

// 最近共同祖先问题 (LCA)
// 最近共同祖先, 该祖先有三种可能性: 一是 p 是 q 的祖先, 二是 q 是 p 的祖先,
// 三是 p 与 q 有一个非 p 非 q 的共同祖先
// 采用后序遍历的方式来进行实现
// 先去左右(得到信息)中(中间节点再进行处理)式的进行访问
// 实现整棵二叉树的后序遍历

// (1) 对于 dfs 递归函数参数的设置, 返回值为一个节点, 函数参数分别为 p, q,
// 以及当前搜索的子树的根节点
// (2) 注意终止条件的设置, 找到 p 或者 q 就可以返回了
// 返回 nullptr 说明在该子树下面没有 p 或者 q
// (3) 对于左右子树搜索完成之后的处理, 左右都找到, 左边找到, 右边找到
// 在后序处理单层递归逻辑时, 回溯传递给 root 结点

class Solution {
public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    // 终止条件 (1) 找到了两个子节点   (2) 除了两个子节点返回他们本身外, nullptr
    // 还要处理二叉树的子节点, 用来返回 left, right 从而处理中间节点
    if (root == nullptr) {
      return nullptr;
    }
    // 找到即可返回, p 或者 q 找到了
    // 立即返回即可
    if (root == q || root == p) {
      return root;
    }

    // 后序遍历
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);

    // 用中间节点进行处理 对祖先节点进行传递即可
    // 左子树 右子树 都各自找到了一个 p q, 即返回中间节点
    if (left != nullptr && right != nullptr) {
      return root;
    }
    // 回溯传递
    if (left == nullptr && right != nullptr) {
      return right;
    } else if (left != nullptr && right == nullptr) {
      return left;
    } else {
      return nullptr;
    }
  }
};