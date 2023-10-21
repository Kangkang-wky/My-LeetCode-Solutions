#include "../include/help.h"

// 最近共同祖先问题
// 最近共同祖先, 该祖先有三种可能性: 一是 p 是 q 的祖先, 二是 q 是 p 的祖先,
// 三是 p 与 q 有一个非 p 非 q 的共同祖先
// 采用后序遍历的方式来进行实现
// 先去左右(得到信息)中(中间节点再进行处理)式的进行访问
// 实现整棵二叉树的后序遍历

class Solution {
public:
  TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    // 终止条件 (1) 找到了两个子节点   (2) 除了两个子节点返回他们本身外, nullptr
    // 还要处理二叉树的子节点, 用来返回 left, right 从而处理中间节点
    if (root == nullptr) {
      return nullptr;
    }
    // 找到即可返回, 这种情况说明 p 和 q 互为祖先节点(祖先节点已经找到),
    // 立即返回即可
    if (root == q || root == p) {
      return root;
    }

    // 后序遍历
    TreeNode *left = lowestCommonAncestor(root->left, p, q);
    TreeNode *right = lowestCommonAncestor(root->right, p, q);

    // 用中间节点进行处理 祖先节点的传递即可
    // 左子树 右子树 都各自找到了一个 p q
    if (left != nullptr && right != nullptr) {
      return root;
    }
    // q, p 找到都在某一个子树
    // 都在左子树
    if (left == nullptr && right != nullptr) {
      return right;
    }
    // 都在右子树
    else if (left != nullptr && right == nullptr) {
      return left;
    }
    // 都没有
    else {
      return nullptr;
    }
  }
};