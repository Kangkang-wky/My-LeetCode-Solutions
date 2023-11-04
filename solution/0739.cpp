#include "../include/help.h"

// TODO 有时间将单调栈这道题目完成
//  维护一个单调栈
//  使用单调栈的**场景**: 通常是在一个一维数组中,
//  要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置
//  本质是用空间来换时间，用单调栈多出来的空间保存一部分有效信息，来维护顺序关系，保留一部分信息

// **通常的做法是**：

//  在单调栈中维护一个有序数组, 做 压栈 或者 弹栈 的操作
//  这部分有序数组的需求就是去右边找比自己大的数字，但是比自己大的还找不到,
//  那么先在栈中存起来，就是一个递减的有序队列，这部分有序队列，等待比自己大的数字出现（在右边）
//  通常要讨论三种情况，遍历的元素 大于栈顶的元素， 等于栈顶的元素，
//  小于栈顶的元素

class Solution {
public:
  vector<int> dailyTemperatures(vector<int> &temperatures) {
    vector<int> answers(temperatures.size(), 0);
    stack<std::pair<int, int>> st;
    for (size_t i = 0; i < temperatures.size(); i++) {
      // 如果栈为空
      if (st.empty()) {
        st.push(std::make_pair(i, std::move(temperatures[i])));
      }
      // 如果栈不为空
      else {
        // 遍历的元素小于等于栈顶
        if (temperatures[i] <= st.top().second) {
          st.push(std::make_pair(i, std::move(temperatures[i])));
        }
        // 遍历的元素大于栈顶
        else {
          while ((!st.empty()) && temperatures[i] > st.top().second) {
            answers[st.top().first] = i - st.top().first;
            st.pop();
          }
          st.push(std::make_pair(i, std::move(temperatures[i])));
        }
      }
    }
    return answers;
  }
};