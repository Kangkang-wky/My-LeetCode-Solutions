#include "../include/help.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
// 注意审题，该问题不是一个有序二叉树
// 完全二叉树插入
// 两个私有成员，一个记录能插入的子节点的队列，一个记录根节点
// 对于有序完全二叉树的初始化，利用层序遍历检查该节点是否哦有左右孩子，若有缺失，将其加入到缺失队列中
// 对于插入问题，插入到缺失队列的第一个即可，同时将插入的节点加入到缺失队列
class CBTInserter {
private:
  queue<TreeNode *> parent_nodes;
  TreeNode *root;

public:
  CBTInserter(TreeNode *root) {
    this->root = root;
    queue<TreeNode *> Q;
    Q.push(root);
    while (!Q.empty()) {
      TreeNode *tmp = Q.front();
      Q.pop();
      if (tmp->left) {
        Q.push(tmp->left);
      }
      if (tmp->right) {
        Q.push(tmp->right);
      }
      // 节点的左右孩子有缺失，加入可插入的父节点队列
      if (!(tmp->left && tmp->right)) {
        parent_nodes.push(tmp);
      }
    }
  }
  TreeNode *get_root() { return root; }

  int insert(int val) {
    TreeNode *child = new TreeNode(val);
    TreeNode *parent = parent_nodes.front();
    int res = parent->val;
    if (!parent->left) {
      parent->left = child;
    } else {
      parent->right = child;
      parent_nodes.pop();
    }
    // 不要忘记将孩子节点插入队列
    parent_nodes.push(child);
    return res;
  }
};

/**
 * Your CBTInserter object will be instantiated and called as such:
 * CBTInserter* obj = new CBTInserter(root);
 * int param_1 = obj->insert(val);
 * TreeNode* param_2 = obj->get_root();
 */