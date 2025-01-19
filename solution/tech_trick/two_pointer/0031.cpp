#include "../include/help.h"

/**
 * @brief     // 贪心算法
    // 经典对 swap 的讨论
    // 要求从小到大， 分析要从原数组中找两个数字，要求
    // (1) 左边的数字小于右边的数字     l  r
    // (2) 左边的数字要尽可能的靠右,    l
    // (3) 右边的数字要尽可能的小，     r
    // (4) **一个不太容易想到的点：左边的小数 与 右边的大数交换后
    // 可以重排此时右边的大树交换后 大数右侧的序列从而让其保证变大的程度最小**

    // 对于此题与交换两个数字不同要增加的是第四点
 * 
 */

class Solution {
public:
  void nextPermutation(vector<int> &nums) {
    // 双指针解题
    // i 表示左边的数字  j 表示右边的数字

    int i = nums.size() - 2; // i 尽可能靠右

    while (i >= 0 && nums[i] >= nums[i + 1]) {
      i--; // i 往左搜索
    }
    // 注意此时 (i + 1, end) 是一个降序排列
    // 但 nums[i] < nums[i + 1]

    if (i >= 0) {
      int j = nums.size() - 1;
      while (j >= 0 && nums[i] >= nums[j]) {
        j--; // j往左搜索,由于(i + 1, end)是一个降序队列，故可以找到第一个大于
             // nums[i] 的数
      }
      swap(nums[i], nums[j]); // 交换第一个大于 nums[i] 的数
    }
    reverse(nums.begin() + i + 1, nums.end()); // 将降序改为升序
  }
};