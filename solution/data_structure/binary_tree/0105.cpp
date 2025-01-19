#include "../include/help.h"

// 已知中序和前序构建二叉树

class Solution {
public:
  TreeNode *dfs(vector<int> &inorder, vector<int> &preorder, int inL, int inR,
                int preL, int preR) {
    // 空了, 说明没有子节点了
    if (preL > preR) {
      return nullptr;
    }

    // 当前节点
    int node_value = preorder[preL];
    TreeNode *node = new TreeNode(node_value);

    // 下面这一行可写可不写, 相当于提前结束, 如果 post 序列为空的话
    if (preL == preR)
      return node;

    // 找到中序
    int k;
    for (k = inL; k <= inR; k++) {
      if (inorder[k] == node_value) {
        break;
      }
    }
    int num_left = k - inL; // 在 inorder[k] 左侧的数的数量
    // 注意 中序要除掉 k , 前序要除掉 preL
    node->left = dfs(inorder, preorder, inL, k - 1, preL + 1, preL + num_left);
    node->right = dfs(inorder, preorder, k + 1, inR, preL + num_left + 1, preR);
    return node;
  }

  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    // if (preorder.size() == 0 || inorder.size() == 0)    return nullptr;
    return dfs(inorder, preorder, 0, inorder.size() - 1, 0,
               preorder.size() - 1);
  }
};