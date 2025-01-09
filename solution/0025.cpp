#include "../include/help.h"

// k 个一组反转链表
// k 是个正数, 最后不足 k 个保留原来得顺序即可

class Solution {
public:
  // 翻转一个子链表，并且返回新的头与尾
  pair<ListNode *, ListNode *> myReverse(ListNode *head, ListNode *tail) {
    ListNode *pre = tail->next;
    ListNode *cur = head;
    while (pre != tail) {
      ListNode *next = cur->next;
      cur->next = pre;
      pre = cur;
      cur = next;
    }
    return {tail, head};
  }

  ListNode *reverseKGroup(ListNode *head, int k) {
    ListNode *dummyhead = new ListNode(0);
    dummyhead->next = head;
    ListNode *pretail = dummyhead;

    while (head != nullptr) {
      ListNode *curtail = pretail;
      // 查看剩余部分长度是否大于等于 k
      for (int i = 0; i < k; ++i) {
        curtail = curtail->next;
        if (!curtail) {
          return dummyhead->next;
        }
      }
      ListNode *next = curtail->next;
      tie(head, curtail) = myReverse(head, curtail);
      // 把子链表重新接回原链表
      pretail->next = head;
      curtail->next = next;
      pretail = curtail;
      head = curtail->next;
    }

    return dummyhead->next;
  }
};