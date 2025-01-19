#include "../include/help.h"

// 中序遍历构建二叉树
// 将链表转换为二叉树

class Solution {
public:
  // TreeNode 二叉树节点
  // 中序遍历构建二叉树即可, 考察一下自己
  TreeNode *sortedListToBST(ListNode *head) {

    // 首先判断是否是 空节点
    if (head == nullptr) {
      return nullptr;
    }

    ListNode *temp = head;

    // 结点计数从 【0, cnt】 采用闭区间索引计数方式
    int cnt = 0;
    while (temp->next != nullptr) {
      temp = temp->next;
      cnt++;
    }
    return dfs(head, 0, cnt);
  }

  TreeNode *dfs(ListNode *head, int left, int right) {

    // 终止条件
    if (left > right) {
      return nullptr;
    }

    int mid = left + (right - left) / 2;
    int step = mid - left;

    ListNode *temp = head;
    while (step-- > 0) {
      temp = temp->next;
    }

    // 当前节点
    TreeNode *node = new TreeNode(temp->val);

    // 根节点的左右子节点
    node->left = dfs(head, left, mid - 1);
    node->right = dfs(temp->next, mid + 1, right);

    return node;
  }
};