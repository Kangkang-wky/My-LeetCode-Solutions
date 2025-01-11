#include "../include/help.h"


/**
 * @brief 以下为二分排序算法部分
 *         
 */

// 算法为找到左边最后一个小于 target 的值, 找到右边第一个大于 target 的值
// lower bound 二分查找写法
// uppper bound 二分查找写法

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {

        int left = 0;
        int right = nums.size() - 1;

        // 找到 left_target 和 right_target 
        // 满足 left_target 本身 = target 且其左边 小于 target 
        // 满足 right_target 本身 = target 且其右边 大于 target


        // 二分方式来做的话
        while(left <= right) {

            int mid = left + (right - left) / 2;

            if (nums[mid] > target) {
                right = mid - 1;
            }
            else if (nums[mid] < target) {
                left = mid + 1;
            }
            // 找到 = 的部分了，
            else {
                // nums[mid] == target 
                if () {

                }
                else {

                }
            }
        }

    }
};