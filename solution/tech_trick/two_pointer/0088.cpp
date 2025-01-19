#include "../include/help.h"

class Solution1 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        
        // nums1[m + i] = nums2[i]
        for(int i = 0; i < n; i++) {
            nums1[m + i] = nums2[i];
        }
        sort(nums1.begin(), nums1.end());
    }
};


/**
 * @brief merge 算法
 * 
 */

class Solution2 {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = nums1.size() - 1;
        m--;
        n--;
        while (n >= 0) {    // 处理完 nums2 数组 
            while (m >= 0 && nums1[m] > nums2[n]) { // 先处理 nums1 数组, 只要 nums1
                swap(nums1[i], nums1[m]);
                i--;
                m--;
            }
            swap(nums1[i], nums2[n]);
            i--;
            n--;
        }
    }
};