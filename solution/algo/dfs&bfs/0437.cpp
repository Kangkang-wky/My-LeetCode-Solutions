#include "../include/help.h"

// 路径总和

class Solution {
private:
    // 以 root 为根节点的路径之和, 即从 root 开始计数
    int rootSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return 0;
        }
        int res = 0;
        if (root->val == targetSum) {       // 说明搜索到了一个
            res++;
        }

        // 以当前节点的左子树为根节点, 判断 target - sum
        res += rootSum(root->left, targetSum - root->val);
        // 以当前节点的右子树为根节点, 判断 target - sum
        res += rootSum(root->right, targetSum - root->val);

        return res;
    }

public:
    int pathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return 0;
        }

        int res = rootSum(root, targetSum);     // 以当前根节点的搜索
        res += pathSum(root->left, targetSum);  // 以当前根节点的左节点搜索
        res += pathSum(root->right, targetSum); // 以当前根节点的右节点搜索
        return res;
    }
};