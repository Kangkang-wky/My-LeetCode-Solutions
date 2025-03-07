#include "../include/help.h"

class Solution1 {
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

class Solution2 {
public:
    ListNode* deleteDuplicates(ListNode* head) {

        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        // 如果 head->val != head->next->val
        if (head->val != head->next->val) {
            head->next = deleteDuplicates(head->next);
        } 
        else {      // 碰到相等的情况
            ListNode* move = head->next;
            while (move->next && head->val == move->next->val) {
                move = move->next;
            }
            return deleteDuplicates(move);
        }
        return head;

    }
};