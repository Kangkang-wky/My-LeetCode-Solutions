#include "../include/help.h"

// 背景: 打算解一个在 GPU 上的 大量数据(query) 的 topk 问题
// 打算在 CPU 上先实现几种 topk 排序作为基准 baseline
// cpu 上的思路大致是: 全局排序, 局部排序(冒泡、快排), 堆排序,
// 基于选择排序(topk 小的数), 双调排序, 桶排序, 基数排序(桶排序的变种?)
// gpu 上首先要做的是优化文件读
// 其次消除多次 launch kernel 以及 cuda memory malloc 的开销
// 消灭掉 bank conflict
// 最后在 gpu 上的排序算法思路参考 sigmod 18(双调排序开创) 以及 sc21 中的几种,
// 还没有看 baseline 中是什么排序,
// 在前面工程都完工的情况下可以尝试测试科研一把双调(bit)排序, 桶排序,
// 以及基数排序 (比较 SC 21 doctor topk) 比较

// 全局排序
class Solution1 {
public:
  vector<int> smallestK(vector<int> &arr, int k) {
    sort(arr.begin(), arr.end());
    return vector<int>(arr.begin(), arr.begin() + k);
  }
};

// 局部排序
// 结果正确, bubble 注意两个问题: 一是 i 的范围代表 top_k, 二是注意 j
// 的范围和顺序决定 arr 数组 top_k 的那些位置在哪里
class Solution2 {
public:
  // bubble_sort
  void bubble_sort_topk(vector<int> &arr, int k) {
    for (size_t i = 0; i < k; i++) { // 局部 k 次
      for (size_t j = arr.size() - 1; j > i; j--) {
        if (arr[j - 1] > arr[j]) {
          swap(arr[j - 1], arr[j]);
        }
      }
    }
  }

  vector<int> smallestK(vector<int> &arr, int k) {
    bubble_sort_topk(arr, k);
    return vector<int>(arr.begin(), arr.begin() + k);
  }
};

// 局部排序
// 快速排序算法, 比较有意思的点是对于 pivot 基准的选择
// 换一种写法 quicksort 的写法以前写的都是填坑法, 这次换成划分法写婴喜爱
// 将[left + 1, right]分成3个部分:
// [left + 1, le)部分所有元素都 <= pivot
// [le, ge]没有看到的部分
// (ge, right]部分所有元素都 >= pivot
class Solution {
public:
  int partition(vector<int> &arr, int left, int right) {
    int pivot = left; // 基准 arr[left]
    // [lt, gt] 还没有做处理的部分
    int lt = left + 1;
    int gt = right;
    while (true) {
      while (lt <= right && arr[lt] < arr[pivot]) {
        lt++;
      }
      while (gt >= left && arr[gt] > arr[pivot]) {
        gt--;
      }
      if (lt > gt) {
        break;
      }
      // 交换 lt gt ++ --
      swap(arr[lt], arr[gt]);
      lt++;
      gt--;
    }
    swap(arr[pivot], arr[gt]);
    return gt;
  }
  // 快排部分递归, 只关心 top k 小的部分, 也就是说对于 topk
  // 内部的排序我们是不关心的
  void quicksort(vector<int> &arr, int left, int right, int k) {
    if (left > right) {
      return;
    }
    int pivot = partition(arr, left, right);
    if (pivot == k)
      return;
    else if (pivot > k) {
      quicksort(arr, left, pivot - 1, k);
    } else {
      quicksort(arr, pivot + 1, right, k);
    }
  }

  vector<int> smallestK(vector<int> &arr, int k) {
    // 边界情况特殊处理
    if (k >= arr.size()) {
      return arr;
    } else if (k <= 0) {
      return {};
    } else {
      quicksort(arr, 0, arr.size() - 1, k);
      return vector<int>(arr.begin(), arr.begin() + k);
    }
  }
};