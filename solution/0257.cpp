#include "../include/help.h"
// 二叉树的所有路径
// 采用回溯法即可, 回溯法的完整模板可以见如下所示

// 递归法: (1)递归参数与返回值 (2)终止条件(3)单层逻辑
// 回溯法
class Solution1 {
private:
  void dfs(TreeNode *node, string path, vector<string> &res) {
    if (node == nullptr)
      return;
    // 先序遍历 dfs
    path += to_string(node->val);
    // 终止条件
    if (node->left == NULL && node->right == NULL) {
      res.push_back(path);
      return;
    }
    if (node->left)
      dfs(node->left, path + "->", res); // 递归
    // 回溯
    if (node->right)
      dfs(node->right, path + "->", res); // 递归
    // 回溯
  }

public:
  vector<string> binaryTreePaths(TreeNode *root) {
    vector<string> res;
    string path;
    dfs(root, path, res);
    return res;
  }
};

// 回溯法完整模板总结
// 二叉树树形数据结构回溯模板总结
class Solution2 {
private:
  // 先序遍历 dfs
  void dfs(TreeNode *node, vector<int> &path, vector<string> &res) {
    if (node == nullptr)
      return;
    path.emplace_back(node->val);
    // 终止条件 处理后 return
    if (node->left == NULL && node->right == NULL) {
      string record;
      for (size_t i = 0; i < path.size(); i++) {
        if (i == 0) {
          record += to_string(path[i]);
        } else {
          record += "->";
          record += to_string(path[i]);
        }
      }
      res.push_back(record);
      return;
    }
    // 非终止 单层逻辑
    if (node->left) {
      dfs(node->left, path, res); // 递归
      path.pop_back();            // 回溯
    }
    if (node->right) {
      dfs(node->right, path, res); // 递归
      path.pop_back();             // 回溯
    }
  }

public:
  vector<string> binaryTreePaths(TreeNode *root) {
    vector<string> res;
    vector<int> path;
    dfs(root, path, res);
    return res;
  }
};