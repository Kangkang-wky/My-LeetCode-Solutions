// 温习一下环检测算法

// 这道题的目的是实现在图中的环存在性检测
// 通过思考大致有三种方法实现
// 一是拓扑排序(topsort), 二是dfs

// 第一种拓扑排序(topsort),判断拓扑序中的节点是否等于总的节点的数量(总体思路为
// bfs)

#include "../include/help.h"

class Solution1 {
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

// dfs 解决环检测问题,主要是想清楚标记三种状态,注意区分当前搜索和之前搜索

class Solution2 {
private:
  // 邻接表以及是否访问过的数组
  vector<vector<int>> Adj;
  // visited 设置三种状态来标记一是未被搜索，二是当前搜集，三是已经搜索(入栈)
  // dfs 若要输出拓扑排序在状态三时进行压栈操作，从栈顶到栈底顺序符合拓扑排序
  vector<int> visited;
  bool flag = true;

public:
  void dfs(int u) {
    if (visited[u] || !flag) { // 图遍历要求是未遍历的节点且没有环
      return;                  // 状态为 1, 2 直接 return
    }
    visited[u] = 1;          // 标记状态为当前搜索
    for (int v : Adj[u]) {   // 访问邻接表
      if (visited[v] == 0) { // 若未被搜索则进行搜索
        dfs(v);
        if (!flag) { // dfs 后有环立即退出
          return;
        }
      } else if (visited[v] == 1) { // 若正在当前搜索说明有环退出
        flag = false;
        return;
      }
    }
    visited[u] = 2; // 当前节点以及它的邻接节点完成搜索,可以压栈
  }

  bool canFinish(int numCourses, vector<vector<int>> &prerequisites) {
    Adj.resize(numCourses);
    visited.resize(numCourses);
    // step1. 构建邻接表
    for (const auto &node : prerequisites) {
      int pre = node[1], cur = node[0];
      Adj[pre].push_back(cur);
    }
    // step2. 图遍历, 对每个节点做dfs
    for (int i = 0; i < numCourses && flag; ++i) {
      dfs(i);
    }
    return flag;
  }
};
