#include "../include/help.h"

/**
 * @brief 说明双指针解法的正确性即可
 *        最大容器： 采用双指针解法即可
 *        双指针：   双指针试探法
 */

// 解法：（1）将左右指针分别置于容器板子的两侧
//       (2) 每次总是向内部移动最短的容器板子, 
//       (3) 完成 n 次移动即可求解最大值

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int res = 0;

        // left < right 
        while (left < right) {
            if (height[left] < height[right]){
                res = std::max(res, (height[left]) * (right - left));
                left++;
            }
            else {
                res = std::max(res, (height[right]) * (right - left));
                right--;
            }
        }
        return res;
    }
};