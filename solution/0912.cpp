#include "../include/help.h"

class Solution1 {
public:
  // quicksort 找到 index 之后重新划分
  int partition(vector<int> &nums, int left, int right) {

    // 中间的标志点
    int mid = left + (right - left) / 2;
    // 暂存标志点的值
    int pivot = nums[mid];

    // 将标志点的值移动到最右边
    swap(nums[mid], nums[right]);

    // 开始进行划分
    int i = left, j = right;

    while (i < j) {
      while (nums[i] <= pivot && i < j)
        i++;
      while (nums[j] >= pivot && i < j)
        j--;
      if (i < j) {
        swap(nums[i], nums[j]);
      }
    }
    // 将 pivot 值还原到停下来的点
    swap(nums[i], nums[right]);

    return i;
  }

  // 快速排序部分
  void quicksort(vector<int> &nums, int left, int right) {

    // 排序完毕
    if (left >= right)
      return;

    // partition 返回的 pivot 是标志点
    int pivot_pos = partition(nums, left, right);
    quicksort(nums, left, pivot_pos - 1);
    quicksort(nums, pivot_pos + 1, right);
  }

  vector<int> sortArray(vector<int> &nums) {

    // 快速排序
    quicksort(nums, 0, nums.size() - 1);
    return nums;
  }
};


class Solution2 {
public:
    vector<int> sortArray(vector<int>& nums) {
        return mergeSort(nums);
    }

private:
    int N;
    vector<int> tmp;
    
    vector<int> mergeSort(vector<int>& nums) {
        N = nums.size();
        tmp = vector<int>(N, 0);
        sort(nums, 0, N - 1);
        return nums;
    }

    // 采用闭区间 [left close, right close]
    void sort(vector<int>& nums, int low, int high) {
        if (low == high) {
            return; // single element no need sort
        }

        int mid = low + (high - low) / 2;
        sort(nums, low, mid);
        sort(nums, mid + 1, high);
        merge(nums, low, mid, high);    // 将 [low, mid] 与 [mid + 1, high] 做 out of place 的 merge
    }

    void merge(vector<int>& nums, int low, int mid, int high) {
        for (int k = low; k <= high; k++) {
            tmp[k] = nums[k];           // out of place
        }

        // i = low 
        // j = mid + 1
        int i = low;
        int j = mid + 1;
        for (int p = low; p <= high; p++) {
            if (i == mid + 1) {           // 前一个数组已经结束
                nums[p] = tmp[j];
                j++; 
            } else if (j == high + 1) {   // 后一个数组已经计数
                nums[p] = tmp[i];
                i++;
            } else if (tmp[i] > tmp[j]) { // 前大后小
                nums[p] = tmp[j];
                j++;
            } else {
                nums[p] = tmp[i];         // 前小后大
                i++;
            }
        }
    }
};
