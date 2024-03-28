#include "../include/help.h"
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

// 链表问题 始终记得解决 pre  cur  next 三个指针
// pre 返回已经操作完的， cur 返回正在操作的， next 返回接下要操作的指针

// 画图, pre 记录已经操作好的节点的指针, cur 操作正要反转的节点
// next 注意提前存好下一个要处理的节点

class Solution {
public:
  ListNode *reverseList(ListNode *head) {
    // reverse list
    ListNode *cur = head;
    ListNode *pre = nullptr;
    while (cur != nullptr) {
      ListNode *next = cur->next;
      cur->next = pre;
      pre = cur;
      cur = next;
    }
    return pre;
  }
};