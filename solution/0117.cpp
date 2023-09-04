#include "../include/help.h"

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};
*/

// 层序遍历即可, 记录下本层节点的个数
// 通过每一次遍历下一层的队列时，访问队列的大小即可判断

// 层序遍历即可, 记录下本层节点的个数
// 通过每一次遍历下一层的队列时，访问队列的大小即可判断
class Solution {
public:
  Node *connect(Node *root) {
    queue<Node *> Q;
    if (root != nullptr)
      Q.push(root);
    while (!Q.empty()) {
      int level_size = Q.size();
      Node *node = nullptr;
      Node *nodepre = nullptr;
      for (int i = 0; i < level_size; i++) {
        if (i == 0) {
          nodepre = Q.front();
          Q.pop();
          // node = nodepre 不要忘记，因为可能本层只有一个节点
          node = nodepre;
        } else {
          node = Q.front();
          Q.pop();
          nodepre->next = node;
          nodepre = nodepre->next;
        }
        if (node->left)
          Q.push(node->left);
        if (node->right)
          Q.push(node->right);
      }
      // 最后一个将其指向置为 nullptr
      nodepre->next = nullptr;
    }
    return root;
  }
};