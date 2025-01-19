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
class Solution1 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
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

class Solution2 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {

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

// 分治法, 采用分治的思想
// 采用经典的 merge 算法即可
class Solution3 {
private:
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

    // 归并排序即可
    ListNode* mergesort_KLists(vector<ListNode*>& lists, int i, int j) {
        if (i == j) return lists[i];
        int mid = i + (j - i) / 2;
    
        auto left = mergesort_KLists(lists, i, mid); // 合并左半部分
        auto right = mergesort_KLists(lists, mid + 1, j); // 合并右半部分
        return mergeTwoLists(left, right); // 最后把左半和右半合并
    }

public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0) {
            return nullptr;
        }
        return mergesort_KLists(lists, 0, lists.size() - 1);
    }

};