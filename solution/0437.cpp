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
        if (root->val == targetSum) {
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
        if (root != nullptr) {
            return 0;
        }

        int res = rootSum(root, targetSum);
        res += pathSum(root->left, targetSum);
        res += pathSum(root->right, targetSum);
        return res;
    }
};