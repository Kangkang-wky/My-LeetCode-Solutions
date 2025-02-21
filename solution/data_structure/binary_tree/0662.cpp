#include "../include/help.h"

/**
 * @brief 注意使用 long long 类型来记录
 * 
 */

class Solution1 {
public:
    int widthOfBinaryTree(TreeNode* root) {
        unsigned long long res = 1;        if(root == nullptr)    return 0;
        queue<pair<TreeNode*, long long>> q;  //pair的第二个位置记录当前是第几个节点
        q.push({root, 1});
        long long width = 0;
        while(!q.empty())
        {   //start是本层起点, index是本层当前遍历到的节点的索引
            long long count = q.size(), start = q.front().second, index; 
            while(count--)
            {
                TreeNode *tmp = q.front().first;
                index = q.front().second;
                q.pop();
                if(tmp->left)   q.push({tmp->left , index * 2 - start * 2});  //防止索引位置太大溢出
                if(tmp->right)  q.push({tmp->right, index * 2 + 1 - start * 2});    
            }
            width = max(width, index - start + 1);
        }
        return width;
        vector<pair<TreeNode *, unsigned long long>> arr;
        arr.emplace_back(root, 1L);
        while (!arr.empty()) {
            vector<pair<TreeNode *, unsigned long long>> tmp;
            for (auto &[node, index] : arr) {
                if (node->left) {
                    tmp.emplace_back(node->left, index * 2);
                }
                if (node->right) {
                    tmp.emplace_back(node->right, index * 2 + 1);
                }
            }
            res = max(res, arr.back().second - arr[0].second + 1);
            arr = move(tmp);
        }
        return res;
    }
};


class Solution2 {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if(root == nullptr)    return 0;
        queue<pair<TreeNode*, long long>> q;  //pair的第二个位置记录当前是第几个节点
        q.push({root, 1});
        long long width = 0;
        while(!q.empty())
        {   //start是本层起点, index是本层当前遍历到的节点的索引
            long long count = q.size(), start = q.front().second, index; 
            while(count--)
            {
                TreeNode *tmp = q.front().first;
                index = q.front().second;
                q.pop();
                if(tmp->left)   q.push({tmp->left , index * 2 - start * 2});  //防止索引位置太大溢出
                if(tmp->right)  q.push({tmp->right, index * 2 + 1 - start * 2});    
            }
            width = max(width, index - start + 1);
        }
        return width;
    }
};