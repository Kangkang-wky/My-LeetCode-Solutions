#include "../include/help.h"

// 根据中序遍历以及后序遍历构造二叉树

class Solution {
public:
  TreeNode *dfs(vector<int> &inorder, vector<int> &postorder, int inL, int inR,
                int postL, int postR) {
    // 空了, 说明没有子节点了
    if (postL > postR) {
      return nullptr;
    }

    // 当前节点
    int node_value = postorder[postR];
    TreeNode *node = new TreeNode(node_value);

    // 下面这一行可写可不写, 相当于提前结束, 如果 post 序列为空的话
    if (postL == postR)
      return node;

    // 找到中序
    int k;
    for (k = inL; k <= inR; k++) {
      if (inorder[k] == node_value) {
        break;
      }
    }
    int num_left = k - inL; // 在 inorder[k] 左侧的数的数量
    // 注意 中序要除掉 k , 后序要除掉 postR
    node->left =
        dfs(inorder, postorder, inL, k - 1, postL, postL + num_left - 1);
    node->right =
        dfs(inorder, postorder, k + 1, inR, postL + num_left, postR - 1);

    return node;
  }

  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    // if (inorder.size() == 0 || postorder.size() == 0)   return nullptr;
    return dfs(inorder, postorder, 0, inorder.size() - 1, 0,
               postorder.size() - 1);
  }
};