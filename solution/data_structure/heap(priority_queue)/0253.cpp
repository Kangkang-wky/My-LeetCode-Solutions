#include "../include/help.h"

// 优先队列即可完成以上操作
// 优先队列模拟结果即可


class Solution1 {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {

        sort(intervals.begin(),intervals.end(),[](vector<int>&a,vector<int>&b){return a[0]<b[0];});//按照开始时间排序
        function<bool(int,int)>cmp=[&](int a,int b){return intervals[a][1]>intervals[b][1];};//结束时间早的优先级高先出队
        priority_queue<int ,vector<int>, decltype(cmp)>pq(cmp);
        int ans=0;
        for(int i=0;i<intervals.size();i++)
        {
            while(!pq.empty()&&intervals[pq.top()][1]<=intervals[i][0])
                pq.pop();//已经结束的会议出队
            pq.push(i);
            ans=max(ans,(int)pq.size());//更新
        }
        return ans;
    }
};


class Solution2 {
public:

    static bool comparasion(const vector<int> &a, const vector<int>& b)
    {
        return a[0] < b[0];
    }

    int minMeetingRooms(vector<vector<int>>& intervals) {

        int n = intervals.size();

        // 按照会议的开始时间进行排序
        sort(intervals.begin(), intervals.end(), comparasion);

        priority_queue<int ,vector<int>, greater<int>>pq;

        int ans = 0;
        for (int i = 0; i < n; i++) {
            while (!pq.empty() && pq.top() <= intervals[i][0]) {
                pq.pop();
            }
            pq.push(intervals[i][1]);
            ans = max(ans, (int)pq.size());
        }
        return ans;
    }
};