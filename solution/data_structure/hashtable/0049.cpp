#include "../include/help.h"

/**
 * @brief string 字母异位词分组
 * 
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