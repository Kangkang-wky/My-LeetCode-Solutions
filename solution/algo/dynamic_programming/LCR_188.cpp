#include "../include/help.h"

class Solution {
public:
  // 买卖股票最佳时机
  int bestTiming(vector<int> &prices) {
    // 要求差价最大
    // 即统计出一个前序的最小值, 统计出
    // 一个在遍历过程中增加的值
    int length = prices.size();

    if (length == 0)
      return 0;

    int min_price_now = prices[0];

    int res_max_diff = 0;
    for (int i = 1; i < length; i++) {
      // 如果当天价格高于目前最低点, 更新结果值
      if (prices[i] > min_price_now) {
        res_max_diff = max(res_max_diff, prices[i] - min_price_now);
      }
      // 如果低于等于最小值
      else {
        min_price_now = min(min_price_now, prices[i]);
      }
    }
    return res_max_diff;
  }
};