#include "../include/help.h"

/**
 * @brief 整数数组 nums 按升序排列，数组中的值 互不相同 。

    在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，
    使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。
    例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
    给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
 
    搜索旋转数组: 采用二分的策略求解
 
 * 
 */



class Solution {


public:
    int search(vector<int>& nums, int target) {
        
        int left = 0;
        int right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[left] <= nums[mid]) {  // 左边有序
                if (nums[left] <= target && target <= nums[mid]) {
                    right = mid - 1;
                }
                else{   // nums[left] > target  || target > nums[mid]
                    left = mid + 1;
                }
            }
            
            else{       // 右边有序
                if (nums[mid] <= target && target <= nums[right]) {
                    left = mid + 1;
                }
                else{     // nums[mid] > target || target > nums[right] 
                    right = mid - 1; 
                }
            }
        }
        return -1;
    }
};