#include "../include/help.h"

/**
 * @brief 有点像模拟题, 固定住左边的指针, 然后右边的指针不断试探着右移
 *        从而计算得到 occ
 *        Description: 无重复字符的最长子串(子串是连续的)
 */


class Solution1 {
public:
    int lengthOfLongestSubstring(string s) {
        // 哈希集合，记录每个字符是否出现过
        unordered_set<char> occ;
        int n = s.size();
        // 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
        int rk = -1, ans = 0;
        // 枚举左指针的位置，初始值隐性地表示为 -1
        for (int i = 0; i < n; ++i) {
            if (i != 0) {
                // 左指针向右移动一格，移除一个字符
                occ.erase(s[i - 1]);
            }
            while (rk + 1 < n && !occ.count(s[rk + 1])) {
                // 不断地移动右指针
                occ.insert(s[rk + 1]);
                ++rk;
            }
            // 第 i 到 rk 个字符是一个极长的无重复字符子串
            ans = max(ans, rk - i + 1);
        }
        return ans;
    }
};


class Solution2 {
public:
    int lengthOfLongestSubstring(string s) {
        std::unordered_set<char> hashmap;
        int res = 0;        // 从 0 开始统计, 防止错误
        int i = 0;
        // 控制 j 从 -1 开始, 相当于一开始右指针在我们左指针的左侧
        int j = -1;

        int str_size = s.size();
        while (j + 1 < str_size && i < str_size) {
            while (!hashmap.count(s[j + 1]) && j + 1 < str_size) {     // 找不到插入
                hashmap.insert(s[j + 1]);
                j++;
            }
            // str[j] 产生冲突了 与其他产生冲突了
            int hashmap_size = hashmap.size();
            res = std::max(res, hashmap_size);
            // 左指针右移, 开始
            // 窗口移动
            hashmap.erase(s[i]);  // 移除收字符继续循环
            i++;
        }
        return res;
    }
};


/**
 * @brief 
 *          滑动窗口 + hashmap 可以加解决以下问题
 * 
 */

class Solution3 {
public:
    int lengthOfLongestSubstring(string s) {
        
        int n = s.length();
        int res = 0;
        int left = 0;
        unordered_map<char, int> cnt; // 维护从下标 left 到下标 right 的字符
        for (int right = 0; right < n; right++) {
            char c = s[right];
            cnt[c]++;
            while (cnt[c] > 1) { // 窗口内有重复字母
                cnt[s[left]]--; // 移除窗口左端点字母
                left++; // 缩小窗口
            }
            res = max(res, right - left + 1); // 更新窗口长度最大值
        }
        return res;
    }
};
 