#include "../include/help.h"

/**
 * @brief 轮转数组
 *        1, 2, 3, 4, 5, 6, 7
 * 轮转后：5, 6, 7, 1, 2, 3, 4
 * 轮转数组：
 */


class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        auto reverse = [&](int i, int j) {
            while (i < j) {
                swap(nums[i++], nums[j--]);
            }
        };

        int n = nums.size();
        k %= n;
        reverse(0, n - 1);
        reverse(0, k - 1);
        reverse(k, n - 1);
    }
};