#include "../include/help.h"

/**
 * @brief 给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。
 *        最长有效括号子串
 *        
 */
/**
 * @brief dp[i] 表示以 i 结尾的子串的 有效括号子串长度，可知 s[i] == ')' 才有统计意义
 *        s[i] == '(' 不具备统计意义
 */

class Solution1 {
public:
    int longestValidParentheses(string s) {
        int max_res = 0, n = s.length();
        vector<int> dp(n, 0);
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {                                            // 第一种情况是说 part '(' ')' : 
                    if (i >= 2) {                                                 // 考虑第一种情况的 dp 递推公式
                        dp[i] = dp[i - 2] + 2;
                    }
                    else {
                        dp[i] = 0 + 2;
                    }
                } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {    // 第二种情况是说  part  '(''('')''('')'')' :      
                    if (i - dp[i - 1] >= 2) {                                     // 考虑第二种情况的 dp 递推公式
                        dp[i] = dp[i - 1] + dp[i - dp[i - 1] - 2] +  2;
                    }
                    else {
                        dp[i] = dp[i - 1] + 2;
                    }
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
                max_res = std::max(max_res, dp[i]);
            }
        }
        return max_res;
    }
};

