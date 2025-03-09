#include "../include/help.h"

/**
 * @brief 快照数组
 *        lower_bound 实现
 */

class SnapshotArray {
    unordered_map<int, vector<pair<int, int>>> history; // 每个 index 的历史修改记录
    int cur_snap_id = 0;    

    // 有序序列中查找第一个不小于给定值的元素的位置
    int lower_bound(vector<pair<int, int>>& nums, int target) {
        int left = 0, right = (int) nums.size() - 1; // 闭区间 [left, right]
        while (left <= right) { // 区间不为空
            // 循环不变量：
            // nums[left-1] < target
            // nums[right+1] >= target
            int mid = left + (right - left) / 2;
            if (nums[mid].first >= target) {
                right = mid - 1; // 范围缩小到 [left, mid-1]
            } else {
                left = mid + 1; // 范围缩小到 [mid+1, right]
            }
        }
        // 循环结束后 left = right+1, 跳出循环时
        // 此时 nums[left-1] < target 而 nums[left] = nums[right+1] >= target
        // 所以 left 就是第一个 >= target 的元素下标
        return left;
    }


public:
    SnapshotArray(int length) {
    }
    
    void set(int index, int val) {
        history[index].emplace_back(cur_snap_id, val);
    }
    
    int snap() {            // 只需把当前快照编号加一（快照编号初始值为 0），返回加一前的快照编号。
        return cur_snap_id++;
    }
    
    int get(int index, int snap_id) {
        auto& h = history[index];
        // 找快照编号 <= snap_id 的最后一次修改记录
        // 等价于找快照编号 >= snap_id+1 的第一个修改记录，它的上一个就是答案
        // <= target 最近的一条记录
        int j = lower_bound(h, snap_id + 1) - 1;        // j 有可能取到 -1
        return j >= 0 ? h[j].second : 0;        
    }
};