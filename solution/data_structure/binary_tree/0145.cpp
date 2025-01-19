// 二叉树的遍历 递归 or 迭代
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
// 递归
class Solution1 {
public:
  void post_travelsal(TreeNode *root, vector<int> &res) {
    if (root == nullptr)
      return;

    if (root->left)
      post_travelsal(root->left, res);
    if (root->right)
      post_travelsal(root->right, res);
    res.emplace_back(root->val);
  }

  vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    post_travelsal(root, res);
    return res;
  }
};

// 迭代法 对访问的节点直接加入到栈中，对处理的节点则是在后面放入一个空节点
// 迭代法 重点是区分遍历的节点即后序遍历的节点,以及要放入到输出队列中的节点,
// 在要放入到输出队列中的节点前放置一个 null

class Solution2 {
public:
  vector<int> postorderTraversal(TreeNode *root) {
    vector<int> res;
    stack<TreeNode *> st;
    if (root != nullptr)
      st.push(root);
    while (!st.empty()) {
      TreeNode *node = st.top();
      if (node != nullptr) {
        st.pop();

        // 后序遍历: 左右中,在栈中倒序放置
        // node是已经压入过栈的节点即已经遍历过的节点,故压入一个null用于下次输出
        st.push(node); // 中
        st.push(nullptr);

        if (node->right)
          st.push(node->right); // 右
        if (node->left)
          st.push(node->left); // 左
      } else {
        st.pop();
        node = st.top();
        st.pop();
        res.emplace_back(node->val);
      }
    }
    return res;
  }
};