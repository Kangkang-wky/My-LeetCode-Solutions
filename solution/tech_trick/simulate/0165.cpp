#include "../include/help.h"

/**
 * @brief 比较版本号, 比较 IP 地址
 * 
 */


class Solution {
public:
    int compareVersion(string version1, string version2) {
        int n = version1.size();
        int m = version2.size();

        vector<long> nums1;
        vector<long> nums2;

        long sum = 0;

        // 按照 . 进行划分比较数字
        for (int i = 0; i < n; i++) {
            if (version1[i] != '.') {
                sum = sum * 10 + version1[i] - '0';
            }
            else{
                nums1.emplace_back(sum);
                sum = 0;
            }
        }
        nums1.emplace_back(sum);
        sum = 0;

        for (int i = 0; i < m; i++) {
            if (version2[i] != '.') {
                sum = sum * 10 + version2[i] - '0';
            }
            else{
                nums2.emplace_back(sum);
                sum = 0;
            }
        }
        nums2.emplace_back(sum);

        for (int i = 0; i < min(nums1.size(), nums2.size()); i++) {
            if (nums1[i] > nums2[i]) {
                return 1;
            }
            else if (nums1[i] < nums2[i]){
                return -1;
            }
        }

        int nums1_size = nums1.size();
        int nums2_size = nums2.size();


        if (nums1_size < nums2_size) {
            nums1 = nums2;
        }
        for (int i = min(nums1_size, nums2_size); i < max(nums1_size, nums2_size); i++) {
            if (nums1[i] != 0) {
                if (nums1_size < nums2_size)    return -1;
                else                            return 1;
            }
        }
        return 0;
    }
};