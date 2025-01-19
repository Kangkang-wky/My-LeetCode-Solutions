#include "../include/help.h"

// 两数相加
// add two number 方法
// 将两数相加即可
// 大数加法进位即可
// 经典问题：两数之和, 采用大数加法来做即可
class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {

    ListNode *dummy = new ListNode(-1);
    ListNode *cur = dummy;

    // 当前的加和 sum
    int sum = 0;
    // 前一位的进位标志位 carry_flag
    bool carry_flag = false;

    while (l1 != nullptr || l2 != nullptr) {
      sum = 0;

      // 第一个加数
      if (l1 != nullptr) {
        sum += l1->val;
        l1 = l1->next;
      }
      // 第二个加数
      if (l2 != nullptr) {
        sum += l2->val;
        l2 = l2->next;
      }
      // 如果有进位标志, 则发起进位, 注意之前的进位即可
      if (carry_flag) {
        sum++;
      }
      // true false 进位即可
      cur->next = new ListNode(sum % 10);
      cur = cur->next;
      carry_flag = sum >= 10 ? true : false;
    }

    if (carry_flag) {
      cur->next = new ListNode(1);
    }

    return dummy->next;
  }
};