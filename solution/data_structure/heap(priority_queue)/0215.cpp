#include "../include/help.h"

/**
 * @brief 堆排序算法
 * 
 */

/**
 * @brief 注意下面的写法是按照下标从 1 开始计算的
 *        建立大顶堆
 * 
 */


class Solution1 {
public:
    // 建立大顶堆
    void buildBigHeap(vector<int> &nums, int length) {
        // 完全二叉树从下往上调整构建大顶堆, i 初始化为最后一个非叶子节点
        for (int i = length/2; i >= 0; --i) {
            adjustHeap(nums, i, length);
        }
    }
    // 堆调整 (规律：左子节点 2*i+1， 右节点 2*i+2)
    void adjustHeap(vector<int> &nums, int i, int length) {
        // 左右子节点, largest保存最后一次被父节点替换的子节点下标
        int left = 2*i+1; int right = 2*i+2; int largest = i;
        // 比较左子节点
        if (left < length && nums[largest] < nums[left]) largest = left;
        // 比较右子节点
        if (right < length && nums[largest] < nums[right]) largest = right;
        // largest != i 说明需要交换，交换完后要检查左右子树是否满足大顶堆的性质，不满足则重新调整子树结构
        if (largest != i) {
            swap(nums[i], nums[largest]);
            adjustHeap(nums, largest, length);
        }
    }
    int findKthLargest(vector<int>& nums, int k) {
        int len = nums.size();
        // 建大顶堆
        buildBigHeap(nums, len);
        // 我们不必要对堆全排序，排序 k - 1 次，根节点即为第 k 大的数
        for (int i = nums.size() - 1; i >= nums.size() - (k-1); --i) {
        	// 根节点（最大值）与最末尾的叶子节点交换位置 
            swap(nums[0], nums[i]);
            // 排除最后一个叶子节点的情况下，再进行堆调整，这样得出的根节点就是次小值了，以此类推
            --len;
            adjustHeap(nums, 0, len);
        }
        return nums[0];
    }
};


/**
 * @brief 注意以下下标同样是从 1 开始的
 *        使用小顶堆, (1) 插入 k 个数字, 在小根堆中
 *                   (2) 将剩余数字与堆顶逐一比较, 剩下的就是第 k 大的数字
 *                   (3) 注意堆排序的技巧
 */


class Solution2 {
public:
    void buildSmallHeap(vector<int> &nums, int length) {
        for (int i = length/2; i >= 0; --i) {
            adjustHeap(nums, i, length);
        }
    }
    void adjustHeap(vector<int> &nums, int i, int length) {
        int left = 2*i+1; int right = 2*i+2; int minimum = i;
        if (left < length && nums[minimum] > nums[left]) minimum = left;
        if (right < length && nums[minimum] > nums[right]) minimum = right;
        if (minimum != i) {
            swap(nums[i], nums[minimum]);
            adjustHeap(nums, minimum, length);
        }
    }
    int findKthLargest(vector<int>& nums, int k) {
        vector<int> smallHeap(nums.begin(), nums.begin()+k);
        int len = smallHeap.size();
        buildSmallHeap(smallHeap, len);
        // 剩下的元素与堆顶比较，若大于堆顶则值进行交换,并维持小顶堆
        for (int i = k; i < nums.size(); ++i) {
            if (nums[i] > smallHeap[0]) {
                swap(smallHeap[0], nums[i]);
                adjustHeap(smallHeap, 0, len);
            }
        }
        return smallHeap[0];
    }
};