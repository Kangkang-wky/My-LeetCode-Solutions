#include "../include/help.h"

// 优先队列即可完成以上操作

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        
        // 按照会议的开始时间进行排序
        sort(intervals.begin(), intervals.end(), [](const vector<int> &a, const vector<int>& b) {
            return a[0] < b[0];
        });

        function<bool(int, int)>cmp=[&](int a, int b) {return intervals[a][1] > intervals[b][1];};

        // 优先队列
        priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);

        
    }
};