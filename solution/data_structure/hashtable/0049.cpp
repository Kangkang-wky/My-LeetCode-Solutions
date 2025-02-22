#include "../include/help.h"

/**
 * @brief string 字母异位词分组
 *        异位词分组, 首先将每个词都进行排序, 排序完成后作为 hashmap 的 key 
 *        对于异位词的分组作为 value, 从而构造一个 group 的异位词
 */


class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        unordered_map<string, vector<string>> hashmap;
        for (string& s : strs) {
            string sorted_s = s;
            std::sort(sorted_s.begin(), sorted_s.end());
            hashmap[sorted_s].push_back(s); 
        }

        vector<vector<string>> res;
        res.reserve(hashmap.size());
        for (auto& [_, value] : hashmap) {
            res.push_back(value);
        }
        return res;
    }
};