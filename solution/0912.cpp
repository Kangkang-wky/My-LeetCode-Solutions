#include "../include/help.h"

class Solution {
public:
  // quicksort 找到 index 之后重新划分
  int partition(vector<int> &nums, int left, int right) {

    // 中间的标志点
    int mid = left + (right - left) / 2;
    // 暂存标志点的值
    int pivot = nums[mid];

    // 将标志点的值移动到最右边
    swap(nums[mid], nums[right]);

    // 开始进行划分
    int i = left, j = right;

    while (i < j) {
      while (nums[i] <= pivot && i < j)
        i++;
      while (nums[j] >= pivot && i < j)
        j--;
      if (i < j) {
        swap(nums[i], nums[j]);
      }
    }
    // 将 pivot 值还原到停下来的点
    swap(nums[i], nums[right]);

    return i;
  }

  // 快速排序部分
  void quicksort(vector<int> &nums, int left, int right) {

    // 排序完毕
    if (left >= right)
      return;

    // partition 返回的 pivot 是标志点
    int pivot_pos = partition(nums, left, right);
    quicksort(nums, left, pivot_pos - 1);
    quicksort(nums, pivot_pos + 1, right);
  }

  vector<int> sortArray(vector<int> &nums) {

    // 快速排序
    quicksort(nums, 0, nums.size() - 1);
    return nums;
  }
};