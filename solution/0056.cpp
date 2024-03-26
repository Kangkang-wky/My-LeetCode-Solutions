#include "../include/help.h"

// 区间合并, 双指针

class Solution1 {
public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    // 存储结果
    vector<vector<int>> res;
    // 先对区间进行排序, 然后用双指针指向前后需要比较的区间
    sort(intervals.begin(), intervals.end());

    // 双指针

    int i = 0;
    while (i < intervals.size()) {
      // 记录目前的 end
      int end_tmp = intervals[i][1];

      int j = i + 1;

      // 移动右指针, 如果右指针指向的区间开始要比目前的 end 小
      // 再次右移右指针, 并更新 end
      while (j < intervals.size() && intervals[j][0] <= end_tmp) {
        end_tmp = max(end_tmp, intervals[i][1]);
        j++;
      }
      res.push_back({intervals[i][0], end_tmp});
      i = j;
    }
    return res;
  }
};

class Solution2 {
private:
  static bool cmp(vector<int> &a, vector<int> &b) {
    if (a[0] == b[0]) {
      return a[1] < b[1];
    } else {
      return a[0] < b[0];
    }
  }

public:
  vector<vector<int>> merge(vector<vector<int>> &intervals) {
    vector<vector<int>> res;
    if (intervals.size() == 0) {
      return res;
    }

    sort(intervals.begin(), intervals.end(), cmp);

    vector<int> tmp;
    int left = intervals[0][0];
    int right = intervals[0][1];

    for (int i = 1; i < intervals.size(); i++) {

      if (right >= intervals[i][0]) {
        right = max(right, intervals[i][1]);
      }
      // 应该更新 intervals
      else {
        tmp.emplace_back(left);
        tmp.emplace_back(right);
        res.emplace_back(tmp);
        tmp.clear();
        left = intervals[i][0];
        right = intervals[i][1];
      }
    }

    return res;
  }
};