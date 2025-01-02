#include "../include/help.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists1(vector<ListNode*>& lists) {
        // lambda function for ListNode value comparasion
        // 注意此处因为 comparasion 部分是一个匿名函数对象, 需要传入以供比较
        if (lists.empty()) {
            return nullptr;
        }

        /*
            匿名函数: (1) 注意优先队列这里 less 是大根堆, greater 是小根堆
        */
        auto cmp = [](const ListNode* a, const ListNode* b) { return a->val > b->val;};
        
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> pri_queue{cmp};

        // 循环添加到优先队列中, 注意放到此处
        for (ListNode* listnode : lists){
            if (listnode != nullptr) {
                pri_queue.push(listnode);
            }
        }

        // listnode head
        ListNode* dummy = new ListNode();
        ListNode* tail = dummy;


        while(!pri_queue.empty()) {
            auto top_node = pri_queue.top();
            tail->next = top_node;
            tail = tail->next;
            pri_queue.pop();
            if (top_node->next != nullptr) {
                pri_queue.push(top_node->next);
            }
        }
        return dummy->next;

    }
};

class Solution {
public:
    ListNode* mergeKLists2(vector<ListNode*>& lists) {

        if (lists.empty()) {
            return nullptr;
        }

        // 此处传入的是
        struct cmp {
            constexpr bool operator()(ListNode* lhs, ListNode* rhs) const 
            {
                return lhs->val > rhs->val;
            }
        };

        std::priority_queue<ListNode*, std::vector<ListNode*>, cmp> pri_queue;

        // 循环添加到优先队列中, 注意放到此处
        for (ListNode* listnode : lists){
            if (listnode != nullptr) {
                pri_queue.push(listnode);
            }
        }

        // listnode head
        ListNode* dummy = new ListNode();
        ListNode* tail = dummy;


        while(!pri_queue.empty()) {
            auto top_node = pri_queue.top();
            tail->next = top_node;
            tail = tail->next;
            pri_queue.pop();
            if (top_node->next != nullptr) {
                pri_queue.push(top_node->next);
            }
        }
        return dummy->next;

    }
};