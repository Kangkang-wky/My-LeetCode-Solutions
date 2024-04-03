#include "../include/help.h"

class MinStack {
private:
  stack<pair<int, int>> st;

public:
  /** initialize your data structure here. */
  MinStack() {}

  void push(int val) {
    if (st.size() == 0) {
      st.push({val, val});
    } else {
      st.push({val, min(val, st.top().second)});
    }
  }

  void pop() { st.pop(); }

  int top() { return st.top().first; }

  int getMin() { return st.top().second; }
};