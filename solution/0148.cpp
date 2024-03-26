#include "../include/help.h"

// solutions in ListNode
class Solution1 {
public:
  ListNode *sortList(ListNode *head) {
    vector<int> sortarray;

    ListNode *my_head = head;
    while (my_head != nullptr) {
      sortarray.emplace_back(my_head->val);
      my_head = my_head->next;
    }
    sort(sortarray.begin(), sortarray.end());

    my_head = head;
    int index = 0;
    while (my_head != nullptr) {
      my_head->val = sortarray[index];
      my_head = my_head->next;
      index++;
    }
    return head;
  }
};

// 递归 归并排序
class Solution2 {
private:
  // 快慢指针找到中间节点
  ListNode *findmid(ListNode *head) {
    ListNode *fast = head, *slow = head;
    ListNode *prev = head;
    while (fast && fast->next) {
      // 记录 slow指针 之前的 一个节点
      prev = slow;
      fast = fast->next->next;
      slow = slow->next;
    }
    // 注意需要将 前一个链表的 next 置为 nullptr
    prev->next = nullptr;
    return slow;
  }
  // 归并两个链表
  ListNode *merge(ListNode *l1, ListNode *l2) {

    // 头部空节点, 用来指向新的链表
    ListNode dummy(0);
    ListNode *tail = &dummy;

    // l1 l2 都不为空
    while (l1 && l2) {
      if (l1->val < l2->val) {
        tail->next = l1;
        l1 = l1->next;
      } else {
        tail->next = l2;
        l2 = l2->next;
      }
      tail = tail->next;
    }
    if (l1 != nullptr) {
      tail->next = l1;
    }
    if (l2 != nullptr) {
      tail->next = l2;
    }
    return dummy.next;
  }

public:
  ListNode *sortList(ListNode *head) {
    // 先解决特殊情况: 没有节点 或者 只有1个节点
    if (head == nullptr || head->next == nullptr)
      return head;

    // 找寻中间节点, 快慢指针去找中间节点, 返回中间节点
    ListNode *mid = findmid(head);
    // 归并左边
    ListNode *left = sortList(head);
    // 归并右边
    ListNode *right = sortList(mid);

    // 合并两个 list
    return merge(left, right);
  }
};