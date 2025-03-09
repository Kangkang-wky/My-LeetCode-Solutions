#include "../include/help.h"

/**
 * @brief 统计逆序对的数量, 可以采用归并排序
 *        [L, R] 分开进行排序
 * 
 */


class Solution {
public:
    int mergeSort(vector<int>& record, vector<int>& tmp, int left, int right) {
        if (left >= right) {
            return 0;
        }

        int mid = left + (right - left) / 2; 
        int inv_count = mergeSort(record, tmp, left, mid) + mergeSort(record, tmp, mid + 1, right);
        int i = left, j = mid + 1, pos = left;
        while (i <= mid && j <= right) {            
            // 只在 i 左移的时候统计逆序对, 逆序对才需要统计, 此事 j 距离 mid + 1前的数字构成与 record[i] 的逆序对
            if (record[i] <= record[j]) {
                tmp[pos] = record[i];
                ++i;
                inv_count += (j - (mid + 1));
            }
            else {
                tmp[pos] = record[j];
                ++j;
            }
            ++pos;
        }
        // 只在 i 左移的时候统计逆序对, 逆序对才需要统计, 此事 j 距离 mid + 1前的数字构成与 record[i] 的逆序对
        for (int k = i; k <= mid; ++k) {
            tmp[pos++] = record[k];
            inv_count += (j - (mid + 1));
        }
        for (int k = j; k <= right; ++k) {
            tmp[pos++] = record[k];
        }
        // merge_sort copy 到暂存空间中, std::copy 操作
        copy(tmp.begin() + left, tmp.begin() + right + 1, record.begin() + left);
        return inv_count;
    }

    int reversePairs(vector<int>& record) {
        int n = record.size();
        vector<int> tmp(n);
        return mergeSort(record, tmp, 0, n - 1);
    }
};