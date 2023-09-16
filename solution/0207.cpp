// TODO 温习一下环检测算法

// 这道题的目的是实现在图中的环存在性检测
// 通过思考大致有三种方法实现
// 一是拓扑排序, 二是dfs, 三是bfs

// 第一种拓扑排序,判断拓扑序中的节点是否等于总的节点的数量

#include "../include/help.h"

class Solution {
public:
  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    vector<vector<int>> Adj(numCourses); // 邻接表
    vector<int> indegree(numCourses, 0); // 记录每个节点的入度

    // step 1. 构建邻接表 以及 入度表
    for (const auto &node : prerequisites) {
      // node[1] 是前驱结点, node[0] 是后继结点
      // node[1] 指向 node[0]
      int cur = node[0], pre = node[1];
      Adj[pre].emplace_back(cur); // pre 指向 cur
      ++indegree[cur];
    }

    // step2 拓扑排序构建, 将入度为0的节点入队
    queue<int> Q;
    for (int i = 0; i < numCourses; ++i) {
      if (indegree[i] == 0) {
        Q.push(i);
      }
    }

    // step3 bfs 开启, bfs 一般思路,
    int cnt = 0;
    while (!Q.empty()) {
      // 入度为 0 的节点出队
      int i = Q.front();
      Q.pop();
      ++cnt;
      // 对于节点 i 指向节点 j 的节点入度都减小 1
      for (const auto j : Adj[i]) { // 检查邻接表, 合适的就进行入队操作
        if (--indegree[j] == 0) {
          Q.push(j);
        }
      }
    }
    return cnt == numCourses;
  }
};