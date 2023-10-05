#include "../include/help.h"

// 背景: 打算解一个在 GPU 上的 大量数据(query) 的 topk 问题
// 打算在 CPU 上先实现几种 topk 排序作为基准 baseline
// cpu 上的思路大致是: 全局排序, 局部排序(冒泡、选择、快排), 堆排序,
// 基于选择排序(topk 小的数), 双调排序, 桶排序
// gpu 上首先要做的是优化文件读
// 其次消除多次 launch kernel 以及 cuda memory malloc 的开销, 以及消灭掉 bank
// conflict
// 最后在 gpu 上的排序算法思路参考 sigmod 18(双调排序开创) 以及 sc21 中的几种,
// 还没有看 baseline 中是什么排序,
// 在前面工程都完工的情况下可以尝试测试科研一把双调(bit)排序, 桶排序,
// 以及基数排序 (比较 SC 21 doctor topk)

class Solution1 {
public:
  vector<int> smallestK(vector<int> &arr, int k) {
    sort(arr.begin(), arr.end());
    return vector<int>(arr.begin(), arr.begin() + k);
  }
};
