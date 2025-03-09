#include "../include/help.h"


/**
 * @brief 大数加法, 注意进位标志即可
 * 
 */

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
      // 如果有进位标志, 则发起进位
      if (carry_flag) {
        sum++;
      }
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