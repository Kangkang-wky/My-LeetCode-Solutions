#include "../include/help.h"

/**
 * @brief 判断字符串子序列, 需要判断 s 是不是 t 的子序列
 * 
 */

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int m = s.size();
        int n = t.size();

        int j_index = 0;




        for (int i = 0; i < n; i++) {
            
            if (t[i] == s[j_index] && j_index < m) {
                j_index++;
            }
            if (j_index == m){
                return true;
            }
        }
        return false;
    }   
};