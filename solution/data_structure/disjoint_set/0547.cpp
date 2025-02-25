#include "../include/help.h"

class Solution {
public:
    int Find(vector<int>& parent, int index) {
        while (index != parent[index]) {
            // 执行路径压缩
            parent[index] = parent[parent[index]];
            
            // 如果不做路径压缩处理的话，就是这一行
            index = parent[index];
        }
        return index;
    }

    int Find_shortpath(vector<int>& parent, int index) {
        if (index != parent[index]) {
            parent[index] = Find_shortpath(parent, parent[index]);
        }
        return parent[index];
    }

    // 合并 index1 和 index2 两个结点
    // index1： 
    // index2:
    void Union(vector<int>& parent, int index1, int index2) {
        int root1 = Find_shortpath(parent, index1);
        int root2 = Find_shortpath(parent, index2);
        
        parent[root1] = root2;
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        int cities = isConnected.size();

        // 并查集, 并查集初始化
        vector<int> parent(cities);

        // 指向根节点
        for (int i = 0; i < cities; i++) {
            parent[i] = i;
        }

        // 完成 Union 操作
        for (int i = 0; i < cities; i++) {
            for (int j = i + 1; j < cities; j++) {
                if (isConnected[i][j] == 1) {
                    Union(parent, i, j);
                }
            }
        }

        // 查询根节点的数量
        int provinces = 0;
        for (int i = 0; i < cities; i++) {
            if (parent[i] == i) {
                provinces++;
            }
        }
        return provinces;
    }
};