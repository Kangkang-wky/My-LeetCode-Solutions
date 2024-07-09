#include "../include/help.h"

// 判断是否有环, 若有环返回第一个入环的节点, 否则返回 NULL 即可

// 使用快慢指针即可
// 设 head 到入口处是 a, 环是 b
// fast ptr 2 step | slow ptr 1 step

// 第一次相遇的时候
// fast = 2 * slow
// fast - slow = n * b

// slow = nb
// fast = 2nb

// 现在 slow = nb = a + x
// 要让 slow 跑 a + nb 步骤就能回到入口处相遇
// 让 第三个指针 从 head 开始 跑 a 步即可

class Solution1 {
public:
  ListNode *detectCycle(ListNode *head) {
    if (head == nullptr) {
      return nullptr;
    }

    // fast slow third 三个指针
    ListNode *fast = head;
    ListNode *slow = head;
    ListNode *third = head;
    bool flag = false;

    // 第一次
    while (fast->next != nullptr) {
      fast = fast->next;
      if (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
        // 第一次快慢指针发生碰撞
        if (slow == fast) {
          flag = true;
          break;
        }
      } else {
        // fast->next == nullptr
        return nullptr;
      }
    }

    if (flag == false) {
      return nullptr;
    }

    // 循环必定会走到 if 分支部分
    if (third == slow) {
      return third;
    }

    while (third->next != nullptr) {
      third = third->next;
      slow = slow->next;
      if (third == slow) {
        return third;
      }
    }

    return nullptr;
  }
};

class Solution2 {
public:
  ListNode *detectCycle(ListNode *head) {
    if (head == nullptr) {
      return nullptr;
    }

    // fast slow third 三个指针
    ListNode *fast = head;
    ListNode *slow = head;
    ListNode *third = head;
    bool flag = false;

    // 第一次
    while (fast->next != nullptr) {
      fast = fast->next;
      if (fast->next != nullptr) {
        fast = fast->next;
        slow = slow->next;
        // 第一次快慢指针发生碰撞
        if (slow == fast) {

          if (third == slow) {
            return third;
          }
          while (third->next != nullptr) {
            third = third->next;
            slow = slow->next;
            if (third == slow) {
              return third;
            }
          }
        }
      } else {
        // fast->next == nullptr
        return nullptr;
      }
    }

    return nullptr;
  }
};