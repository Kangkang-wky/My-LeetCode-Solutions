// 温习一下拓扑, 可参考0207.cpp

#include "../include/help.h"

// bfs

class Solution {
public:
  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    vector<int> topsort;
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
      topsort.emplace_back(i);
      ++cnt;
      // 对于节点 i 指向节点 j 的节点入度都减小 1
      for (const auto j : Adj[i]) { // 检查邻接表, 合适的就进行入队操作
        if (--indegree[j] == 0) {
          Q.push(j);
        }
      }
    }
    if (cnt == numCourses) {
      return topsort;
    } else {
      topsort.clear();
      return topsort;
    }
  }
};

// dfs 在状态三时对已经搜索节点进行压栈操作

class Solution2 {
private:
  // 邻接表以及是否访问过的数组
  vector<vector<int>> Adj;
  // visited 设置三种状态来标记一是未被搜索，二是当前搜集，三是已经搜索(入栈)
  // dfs 若要输出拓扑排序在状态三时进行压栈操作，从栈顶到栈底顺序符合拓扑排序
  vector<int> visited;
  stack<int> topsort;
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
    topsort.push(u);
  }

  vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites) {
    vector<int> res;
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
    if (!flag) {
      return res;
    } else {
      while (!topsort.empty()) {
        res.emplace_back(topsort.top());
        topsort.pop();
      }
      return res;
    }
  }
};
