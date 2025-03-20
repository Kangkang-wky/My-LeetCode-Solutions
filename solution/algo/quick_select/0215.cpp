#include "../include/help.h"

class Solution {
private:
  // 基准划分, 记忆化模板
  int partition(vector<int> &nums, int left, int right) {
    int mid = left + (right - left) / 2;              // 选取中间元素作为切分值
    swap(nums[mid], nums[right]);                     // 将切分值放到右边界避免加入元素的划分
    int partition = nums[right], i = left, j = right; // 双指针从左右边界开始，分别找到要交换的元素
    while (i < j) {
      while (i < j && nums[i] >= partition) {
        i++; // 找到左侧小于切分值的元素
      }
      while (j > i && nums[j] <= partition) {
        j--; // 找到右侧大于切分值的元素【因为是找大于，即使j从right开始，right也不会被选中】
      }
      if (i < j) {
        swap(nums[i], nums[j]); // 将大于元素放到左侧，小于元素放到右侧
      }
    }
    swap(nums[i], nums[right]); // i最后停留的位置一定是右侧首个小于切分值的元素，与切分值交换
    return i;                   // 返回 partition 分割点
  }

  // 基准划分, 记忆化模板
  int partition2(vector<int> &nums, int left, int right) {
    int mid = left + (right - left) / 2; // 选取中间元素作为切分值
    swap(nums[mid], nums[left]); // 将切分值放到右边界避免加入元素的划分
    int partition = nums[left], i = left,
        j = right; // 双指针从左右边界开始，分别找到要交换的元素
    while (i < j) {
      while (j > i && nums[j] <= partition)
        j--; // 找到右侧大于切分值的元素【因为是找大于，即使j从right开始，right也不会被选中】
      nums[i] = nums[j];
      while (i < j && nums[i] >= partition)
        i++; // 找到左侧小于切分值的元素
      nums[j] = nums[i];
    }
    nums[i] = partition;
    return i;
  }

  int quickSortK(vector<int> &nums, int k, int left, int right) {
    int index = partition2(nums, left, right); // 划分 [left, right] 区间即可, 返回 pivot 坐标
    if (index == k - 1) return nums[index];
    
    // 每次只需要快排另外一半
    if (index < k - 1) {
      return quickSortK(nums, k, index + 1, right);
    }
    else {
      return quickSortK(nums, k, left, index - 1);
    }
  }

public:
  int findKthLargest(vector<int> &nums, int k) {
    // 要快速选择第 k 大的元素
    return quickSortK(nums, k, 0, nums.size() - 1); // 快排整个区间
  }
};