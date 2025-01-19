#include "../include/help.h"

// 判断链表是否成环
// 采用快慢指针的方式判断链表是否成环即可

class Solution {
public:
  bool hasCycle(ListNode *head) {
    if (head == nullptr) {
      return false;
    }

    ListNode *fast = head;
    ListNode *slow = head;

    while (fast->next != nullptr) {
      fast = fast->next;
      if (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
        // 快慢指针发生碰撞
        if (slow == fast) {
          return true;
        }
      } else {
        // fast->next == nullptr
        return false;
      }
    }
    return false;
  }
};