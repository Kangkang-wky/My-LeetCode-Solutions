#include "../include/help.h"

class Solution {
public:
  ListNode *oddEvenList(ListNode *head) {
    if (head == nullptr) {
      return head;
    }
    ListNode *evenHead = head->next;
    ListNode *even = evenHead;
    ListNode *odd = head;
    // odd 指向 奇节点
    // even 指向 偶节点
    while (even != nullptr && even->next != nullptr) {
      odd->next = even->next; // odd 下一个指向偶节点的下一个即奇节点
      odd = odd->next;        // odd 前移
      even->next = odd->next; // even 下一个指向奇节点的下一个即奇节点
      even = even->next; // even 前移
    }
    odd->next = evenHead;
    return head;
  }
};