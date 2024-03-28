#include "../include/help.h"

// 0, 1, 2排序问题
// 偷懒的做法是 通过 0, 1, 2 遍历进行置换操作

class Solution1 {
public:
  void sortColors(vector<int> &nums) {
    int cnt_0 = 0;
    int cnt_1 = 0;
    int cnt_2 = 0;

    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] == 0) {
        cnt_0++;
      }
      if (nums[i] == 1) {
        cnt_1++;
      }
      if (nums[i] == 2) {
        cnt_2++;
      }
    }
    for (int i = 0; i < nums.size(); i++) {
      if (i >= 0 && i < cnt_0) {
        nums[i] = 0;
      } else if (i >= cnt_0 && i < cnt_0 + cnt_1) {
        nums[i] = 1;
      } else {
        nums[i] = 2;
      }
    }
  }
};

// 另外一种做法是双指针，一个指针负责处理 0， 从头部开始，一个指针负责处理2，
// 从尾部开始
class Solution2 {
public:
  void sortColors(vector<int> &nums) {
    int left = 0;
    int right = nums.size() - 1;
    int i = 0;

    // 保持 [0, left) 为 0
    // 保持 (right, nums.size() - 1] 为 2
    // 经过 遍历之后, [left, right] 之间为 1

    // 循环可以继续下去的条件
    while (i <= right) {
      if (nums[i] == 0) {
        swap(nums[left], nums[i]);
        i++;
        left++;
      } else if (nums[i] == 2) {
        swap(nums[right], nums[i]);
        i++;
        right--;
      } else {
        i++;
      }
    }
  }
};