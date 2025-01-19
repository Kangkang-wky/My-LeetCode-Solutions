#include "../include/help.h"

// 寻找重复数, hash table 即可

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_map<int, bool> map;
        for(int num : nums) {
            if(map[num]) return num;
            map[num] = true;
        }
        return -1;
    }
};