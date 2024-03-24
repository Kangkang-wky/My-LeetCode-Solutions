#include "../include/help.h"

// 排序法
// 要求最短无序数组, 即排序后就变为有序数组, 那么排序后分别求最长前缀数组
// 最长后缀数组即可
class Solution1 {
public:
  int findUnsortedSubarray(vector<int> &nums) {
    // 注意本身就有序的情况需要输出 0
    if (is_sorted(nums.begin(), nums.end())) {
      return 0;
    }
    vector<int> sort_array(nums);
    sort(sort_array.begin(), sort_array.end());
    int left = 0, right = nums.size() - 1;
    while (nums[left] == sort_array[left]) {
      left++;
    }
    while (nums[right] == sort_array[right]) {
      right--;
    }
    return right - left + 1;
  }
};

// 双指针
// 分析: 要求 nums1 中 有序  nums2 中 无序, nums3 中有序
// 而且满足 对于 nums2 中的数,  nums1 中的数 小于 nums2 中的最小值
// 且 num3 中的数大于 nums2 中的最大值
//   nums_i < min_minsize (num_i+1_j) 最小值
//   nums_j > max_maxsize (num_i_j-1) 最大值
//  nums2 区间是 [i+1, j-1]
class Solution2 {
public:
  int findUnsortedSubarray(vector<int> &nums) {

    int min_num = nums[nums.size() - 1];
    int max_num = nums[0];
    int left = 0, right = -1; // 注意如果全是有序的时候, 初始化小心
    for (int i = 0; i < nums.size(); i++) {

      // 从左到右 维护一个当前序列到此为止的最大值, 正常的升序序列
      // 应该每次都要更新 max_num 但是在 nums2 中却不一定能够
      if (nums[i] < max_num) {
        right = i;
      } else {
        max_num = nums[i];
      }
      // 从右到左 维护一个当前序列到此的最小值, 正常的升序序列, 应该
      // 每次到此都要更新 min_num, 但是在 nums2 中 left 位置不能正常更新
      if (nums[nums.size() - 1 - i] > min_num) {
        left = nums.size() - 1 - i;
      } else {
        min_num = nums[nums.size() - 1 - i];
      }
    }
    return right - left + 1;
  }
};