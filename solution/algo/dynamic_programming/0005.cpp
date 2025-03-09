#include "../include/help.h"

/**
 * @brief 返回字符串中的最长回文子串, 最优子结构, 判断
 *        dp[i][j] 表示 从 i 开始 到 j 结束的子串是否为 回文串
 *        
 *        要求 i < j
 *        if (dp[i]不等于dp[j]) 那么它不是回文子串
 *        else (dp[i] == dp[j])  dp[i][j] 是不是回文串, 要去判断 dp[]
 *          i == j true
 *          i + 1 = j  true
 *          j - i > 1 三个数, 要去判断 dp[i+1][j-1] 是不是回文串
 */

class Solution {
public:
    string longestPalindrome(string s) {
        
        int n = s.size();

        if (n < 2) {
            return s;
        }

        int max_len = 0;
        int max_index = 0;
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }

        //根据递推公式的顺序
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j <= n - 1; j++) {
                if (s[i] != s[j]) { 
                    dp[i][j] = false;
                }
                else{
                    if (j - i <= 1) {
                        dp[i][j] = true;
                    }
                    else{
                        dp[i][j] = dp[i+1][j-1];
                    }

                    if (dp[i][j] == true) {
                        if (max_len < std::max(max_len, j - i + 1)) {
                            max_len = j - i + 1;
                            max_index = i;
                        }
                    }
                }
            }
        }

        return s.substr(max_index, max_len);
    }
};