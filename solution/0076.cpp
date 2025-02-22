#include "../include/help.h"

/**
 * @brief 采用双指针-滑动窗口的方式来解决以下问题
 *        给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。
 *        如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 
 * 
 */

class Solution {
public:
    string minWindow(string s, string t) {
        std::unordered_map<char, int> hashmap;
        int s_size = s.size();
        int tlen = t.size();  
        for (char& c : t) {
            ++hashmap[c];
        }

        queue<pair<char, int>> que;         // 用于存储当前窗口内的字符及其索引, 窗口一前一后一定是  
        int min_val = numeric_limits<int>::max();  
        pair<int, int> res = { 0, 0 };  

        // 遍历 s 中的每个字符  
        for (int i = 0; i < s_size; ++i) {
            // 仅处理在 mp 中存在的字符且对应频率大于 0, s[i] 是否应该加入到 que 中  
            if (hashmap.find(s[i]) != hashmap.end()) {
                que.push({s[i], i}); // 将字符及其索引入队  
                --hashmap[s[i]]; // 减少该字符的计数  
            }

            // 检查当前窗口是否包含 t 中所有字符  
            bool ok = true;
            for (auto& pr : hashmap) {     // hashmap 都等于 0 时, 表明
                if (pr.second > 0) { // 如果还有未满足的字符，标记窗口无效  
                    ok = false;
                    break;
                }
            }

            // 如果当前窗口有效，则开始收缩窗口  
            if (ok) {
                // 尝试收缩窗口，确保所有字符计数满足条件, 直到不满足条件
                while (!que.empty() && hashmap[que.front().first] < 0) {
                    ++hashmap[que.front().first];  
                    que.pop();  
                }

                int res_len = que.back().second - que.front().second + 1; 
                min_val = std::min(min_val, res_len);
                if (min_val == res_len) {
                    res.first = que.front().second;  
                    res.second = res_len;
                }

                // 如果窗口是非空的, 此时再做类似于左指针右移的操作
                // 将 queue 中字符 front 部分排除一个
                if (!que.empty()) {
                    ++hashmap[que.front().first];
                    que.pop();
                }
            }
        }

        // 返回最小覆盖子串，若无则返回空字符串  
        return res.second == 0 ? "" : s.substr(res.first, res.second);
    }
};