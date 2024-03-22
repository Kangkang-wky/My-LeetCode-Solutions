#include "../include/help.h"

// 双指针
//  [A]  [left, right]  [B]
// left right 之间是最短无序连续子数组
// 左边有序  num_i < num_j  if (i < j)
// 右边同上有序
// 两个指针分别找到 left 与 right

// 从左到右维护一个最大值max,在进入右段之前，那么遍历到的nums[i]都是小于max的，我们要求的end就是遍历中最后一个小于max元素的位置；
// 同理，从右到左维护一个最小值min，在进入左段之前，那么遍历到的nums[i]也都是大于min的，要求的begin也就是最后一个大于min元素的位置。

class Solution {
public:
  int findUnsortedSubarray(vector<int> &nums) {}
};