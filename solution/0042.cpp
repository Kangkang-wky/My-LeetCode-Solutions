#include "../include/help.h"

// 2024 is coming, practice on 2023/12/24
// 元旦前夕, 饭局被放鸽子, 闲来无事刷题, 想起刷题以来似乎都没有写过接雨水
// 来写写接雨水, 悲！ 希望明年...

// 暴力做法是按照列来进行划分的, 计算每一列上的水柱可以有多高
class Solution1 {
public:
  int trap(vector<int> &height) {
    int sum = 0;
    // 0 以及 最后一个柱子接不到水
    for (int i = 1; i < height.size() - 1; i++) {
      int lhs = height[i], rhs = height[i];

      // 寻找右边最大的柱子
      for (int j = i + 1; j < height.size(); j++) {
        if (height[j] > rhs) {
          rhs = height[j];
        }
      }
      // 寻找左边最大的柱子
      for (int j = i - 1; j >= 0; j--) {
        if (height[j] > lhs) {
          lhs = height[j];
        }
      }
      sum += std::min(lhs, rhs) - height[i];
    }
    return sum;
  }
};

// double pointer
// 很容易想到的一点是计算每个柱子左边高和右边高是有计算冗余的
// 可以遍历两遍存储下来
class Solution2 {
public:
  int trap(vector<int> &height) {

    if (height.size() <= 2) {
      return 0;
    }

    vector<int> lhs_max(height.size(), 0);
    vector<int> rhs_max(height.size(), 0);
    int size = lhs_max.size();

    // 左边比它高的柱子
    lhs_max[0] = height[0];
    for (int i = 1; i < size; i++) {
      lhs_max[i] = std::max(lhs_max[i - 1], height[i]);
    }
    // 右边比它高的柱子
    rhs_max[size - 1] = height[size - 1];
    for (int i = size - 2; i >= 0; i--) {
      rhs_max[i] = std::max(rhs_max[i + 1], height[i]);
    }

    // 按列求和
    int sum = 0;
    for (int i = 0; i < size; i++) {
      sum += std::min(lhs_max[i], rhs_max[i]) - height[i];
    }
    return sum;
  }
};
