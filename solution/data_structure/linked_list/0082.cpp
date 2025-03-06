#include "../include/help.h"

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        
        ListNode* dummy = head;
        ListNode* cur = head;
        // 去重
        while (cur != nullptr && cur->next != nullptr) {
            ListNode* now = cur;  
            if (cur->val != cur->next->val) {
                cur = cur->next;
            }
            else{
                while (cur != nullptr && cur->next != nullptr && cur->val == cur->next->val) {
                    cur = cur->next;
                }
                now->next = cur->next;
                cur = cur->next;
            }
        }
        return dummy;
    }
};