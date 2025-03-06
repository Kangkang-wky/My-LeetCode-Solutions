#include "../include/help.h"


/**
 * @brief 三数之和, a, b, c 固定第一个数, 然后, 将第二, 三个数作为双指针
 * 
 */


class Solution1 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;        
        
        // 枚举 a, 固定第一个数
        for (int first = 0; first < n; ++first) {
            if (first > 0 && nums[first] == nums[first - 1]) {    //  优化当前的搜索, 重复数字, 排除 
                continue;
            }
            // c 对应的指针初始指向数组的最右端
            int third = n - 1;
            int target = - nums[first];
            // 枚举 b
            for (int second = first + 1; second < n; ++second) {
                if (second > first + 1 && nums[second] == nums[second - 1]) {     // 优化当前的搜索, 重复数字, 排除
                    continue;
                }
                // 需要保证 b 的指针在 c 的指针的左侧, c 指向的数太大, 不断左移
                while (second < third && nums[second] + nums[third] > target) {
                    --third;
                }
                if (second == third) {    // 优化当前的搜索, 如果 b 的坐标 == c 的坐标了, b 超过 c, 剪枝
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    res.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return res;
    }
};

/**
 * @brief 三数之和：凑出 0 部分
 *  给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k 
 *  同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。
 *
 *  注意：答案中不可以包含重复的三元组。
 */

class Solution2 {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        for (int first = 0; first < n; first++) {
            // 数字重复直接跳过, 要求的是和为 0 且不重复的三元组
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
        
            int third = n - 1;
            int target = -nums[first];

            for (int second = first + 1; second < n; second++) {
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                
                while (second < third && nums[second] + nums[third] > target) {
                    third--;
                }
                if (second == third) {      // 如果 second 和 third 碰上意味着 不再存在对应的解
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    res.push_back({nums[first], nums[second], nums[third]});
                }
            }
        }
        return res;
    }
};