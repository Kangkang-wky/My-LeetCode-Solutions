#include "../include/help.h"


class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode();
        ListNode* cur = dummy;
        // 两个 list 都不为空
        while(list1 != nullptr && list2 != nullptr) {
            if (list1->val < list2->val) {
                cur->next = list1;
                list1 = list1->next;
            }
            else {
                cur->next = list2;
                list2 = list2->next;
            }
            cur = cur->next;
        }

        if (list1 == nullptr) { // list1 为空
            cur->next = list2;
        }
        else {                  // list2 为空
            cur->next = list1;
        }

        return dummy->next;
    }
};