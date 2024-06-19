#include "../include/help.h"

// 把这段代码从一个串行程序, 改造为并行程序, 同样也可以用异或指令
// 来减少指令依赖的问题

class Solution {
public:
  int singleNumber(vector<int> &nums) {
    int res = 0;
    for (int i = 0; i < nums.size(); i++) {
      res = res ^ nums[i];
    }
    return res;
  }
};