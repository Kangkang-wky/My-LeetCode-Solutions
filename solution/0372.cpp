#include "../include/help.h"

/**
 * @brief 设计一个最大栈数据结构，既支持栈操作，又支持查找栈中最大元素。
        实现 MaxStack 类：

        MaxStack() 初始化栈对象
        void push(int x) 将元素 x 压入栈中。
        int pop() 移除栈顶元素并返回这个元素。
        int top() 返回栈顶元素，无需移除。
        int peekMax() 检索并返回栈中最大元素，无需移除。
        int popMax() 检索并返回栈中最大元素，并将其移除。如果有多个最大元素，只要移除 最靠近栈顶 的那个。
 * 
 */




class MaxStack {
private:
    multimap<int, list<int>::iterator> map;
    list<int> list;
public:
    /** initialize your data structure here. */
    MaxStack() {

    }

    void push(int x) {
        list.push_back(x);
        map.insert({x, --list.end()});
    }

    int pop() {
        auto lastIt = --list.end();
        int ans = *lastIt;
        auto toBeRemovedIt = --map.upper_bound(ans);
        map.erase(toBeRemovedIt);
        list.erase(lastIt);
        return ans;
    }

    int top() {
        return list.back();
    }

    int peekMax() {
        return map.rbegin()->first;
    }

    int popMax() {
        auto lastMapIt = --map.end();
        auto listIt = lastMapIt->second;
        int ans = *listIt;
        map.erase(lastMapIt);
        list.erase(listIt);
        return ans;
    }
};