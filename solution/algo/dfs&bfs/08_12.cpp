#include "../include/help.h"

/**
 * @brief n 皇后问题: 注意对角线部分如何处理，如正对角线和反对角线, 正对角线行列相减, 反对角线行列相加
 * 
 */

class Solution {
public:
    void dfs(int step, vector<int> &temp, vector<vector<int>> &res_num, vector<bool> &hashmap, \
            unordered_set<int> &diagnoals_1, unordered_set<int> &diagnoals_2, int n) {

        if (step == n) {    // 循环终止条件
            res_num.emplace_back(temp);
            return;
        }
        for (int i = 0; i < n; i++) {
            // 整行整列没有问题, 对角线部分加入即可
            if (hashmap[i] == false &&  diagnoals_1.find(step - i) == diagnoals_1.end() \
                 && diagnoals_2.find(step + i) == diagnoals_2.end()) {  \
                
                hashmap[i] = true;
                temp.emplace_back(i);
                diagnoals_1.insert(step - i);
                diagnoals_2.insert(step + i);
                
                dfs(step + 1, temp, res_num, hashmap, diagnoals_1, diagnoals_2, n);     
                
                diagnoals_1.erase(step - i);
                diagnoals_2.erase(step + i);
                hashmap[i] = false;
                temp.pop_back();
            
            }
        }
    } 


    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<int> temp;
        vector<bool> hashmap(n, false);
        vector<vector<int>> res_num;
        unordered_set<int> diagnoals_1;
        unordered_set<int> diagnoals_2;
        
        dfs(0, temp, res_num, hashmap, diagnoals_1, diagnoals_2, n);

        for (int i = 0; i < res_num.size(); i++) {
            vector<string> solution;
            for (int j = 0; j < res_num[i].size(); j++) {
                string row(size_t(n), (char)'.');
                row.replace(res_num[i][j], 1, "Q");
                solution.emplace_back(row);
            }
            res.emplace_back(solution);
        }
        return res;
    }
};