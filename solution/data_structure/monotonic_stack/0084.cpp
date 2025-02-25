#include "../include/help.h"

// 84. 柱状图中最大的矩形
// 84. Largest Rectangle in Histogram

// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
// 求在该柱状图中，能够勾勒出来的矩形的最大面积。

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n, -1);
        stack<int> st;
        
        // st 维护单调栈, 维护的是一个单调递增栈
        // left 记录的是左边第一个比自己小的
        for (int i = 0; i < n; i++) {
            while (!st.empty() && heights[i] <= heights[st.top()]) {
                st.pop();
            }
            if (!st.empty()) {
                left[i] = st.top();
            }
            st.push(i);
        }

        vector<int> right(n, n);
        st = stack<int>();

        // st 维护单调栈, right 记录右边第一个比自己小的, 单调栈的内部维护逻辑是
        // 维护栈内单调递增
        for (int i = n - 1; i >= 0; i--) {
            while (!st.empty() && heights[i] <= heights[st.top()]) {
                st.pop();
            }
            if (!st.empty()) {
                right[i] = st.top();
            }
            st.push(i);
        }

        // left 是左边第一个比自己小的
        // right 是右边第一个比自己大的
        // 那么中间的 [left + 1, right - 1] 就是我们需要的矩形的大小


        int res = 0;
        for (int i = 0; i < n; i++) {
            res = std::max(res, heights[i] * (right[i] - left[i] - 1));
        }
        return res;
    }
};