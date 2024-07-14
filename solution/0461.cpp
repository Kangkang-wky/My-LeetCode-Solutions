#include "../include/help.h"

// 汉明距离的问题
// 返回 x 与 y 的二进制位不同的位数

class Solution1 {
public:
  int hammingDistance(int x, int y) {
    // 异或运算即可
    int dis = x ^ y;
    // 判断 dis 中 1 的位数即可
    int res = 0;

    while (dis) { // //每一次运算消去一个1，直到为0终止循环
      dis &= (dis - 1); // dis = dis & (dis - 1)
      res++;
    }
    return res;
  }
};

class Solution2 {
public:
  int hammingDistance(int x, int y) {
    // 异或运算即可
    int dis = x ^ y;
    // 判断 dis 中 1 的位数即可
    int res = 0;

    while (dis) { // 直到 dis == 0 退出即可
      // dis 在最后一个1 处进行 & 运算统计是 1, 则 + 1
      // 统计是 0, 则保持原来的值

      res = dis & 1 ? res + 1 : res;
      dis = dis >> 1;
    }
    return res;
  }
};