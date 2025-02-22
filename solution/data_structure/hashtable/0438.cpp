#include "../include/help.h"

/**
 * @brief 找出所有的字母异位词子串
 *        给一个长字符串 s, 给一个短字符串 p, 要求找出 s 中所有的与p 相关的字母异位词子串
 */

class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        
        vector<int> res;
        int p_size = p.size();
        int s_size = s.size();

        vector<int> hashmap(26, 0);
        vector<int> temp_hashmap(26, 0);
        
        for (int i = 0; i < p_size; i++) {
            hashmap[p[i] - 'a'] += 1; 
        }

        if (s_size < p_size) {
            return res;
        }
        else {
            for (int i = 0; i < p_size; i++) {
                temp_hashmap[s[i] - 'a'] += 1;
            
            }
            if (hashmap == temp_hashmap) {
                res.push_back(0);
            }

            for (int i = 1; i < s_size - p_size + 1; i++) {
                temp_hashmap[s[i - 1] - 'a'] -= 1;
                temp_hashmap[s[i + p_size - 1] - 'a'] += 1;
                if (hashmap == temp_hashmap) {
                    res.push_back(i);
                }
            }
        }
        return res;
    }
};