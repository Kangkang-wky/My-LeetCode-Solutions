#include "../include/help.h"

// 非递归版本 左闭右闭
class Solution1 {
public:
  int search(vector<int> &nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      int num = nums[mid];
      if (num == target) {
        return mid;
      } else if (num > target) {
        right = mid - 1;
      } else {
        left = mid + 1;
      }
    }
    return -1;
  }
};

// 递归版本 左闭右闭，递归搜索
class Solution2 {
private:
  int binarySearch(vector<int> &nums, int target, int left, int right) {
    // 搜索终止条件
    if (left > right) {
      return -1;
    }

    int mid = left + (right - left) / 2;
    if (target < nums[mid]) {
      return binarySearch(nums, target, left, mid - 1);
    } else if (target > nums[mid]) {
      return binarySearch(nums, target, mid + 1, right);
    } else {
      return mid;
    }
  }

public:
  int search(vector<int> &nums, int target) {
    return binarySearch(nums, target, 0, nums.size() - 1);
  }
};