#include "../include/help.h"

// lower bound 二分查找写法
// uppper bound 二分查找写法

class Solution {
    // lower_bound 返回最小的满足 nums[i] >= target 的下标 i
    // 如果数组为空，或者所有数都 < target，则返回 nums.size()
    // 要求 nums 是非递减的，即 nums[i] <= nums[i + 1]
    int lower_bound(vector<int>& nums, int target) {
        int left = 0, right = (int) nums.size() - 1; // 闭区间 [left, right]
        while (left <= right) { // 区间不为空
            // 循环不变量：
            // nums[left-1] < target
            // nums[right+1] >= target
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid - 1; // 范围缩小到 [left, mid-1]
            } else {
                left = mid + 1; // 范围缩小到 [mid+1, right]
            }
        }
        // 循环结束后 left = right+1
        // 此时 nums[left-1] < target 而 nums[left] = nums[right+1] >= target
        // 所以 left 就是第一个 >= target 的元素下标
        return left;
    }

public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int start = lower_bound(nums, target);

        // 返回失败结果的可能条件
        if (start == nums.size() || nums[start] != target) {
            return {-1, -1}; // nums 中没有 target
        }
        
        // 其余情况应该需要返回成功的结果
        int end = lower_bound(nums, target + 1) - 1;
        return {start, end};
    }
};