#include "../include/help.h"

class Solution {
public:
    bool check(TreeNode* left, TreeNode* right) {

        // 如果二者都为空则返回 true
        if (left == nullptr && right == nullptr) {
            return true;
        }

        // 判断

        if (left == nullptr || right == nullptr) {
            return false;
        }

       
        int left_val = left->val;
        int right_val = right->val;
            
        return left_val == right_val && check(left->left, right->right) && check(left->right, right->left);
    }

    bool isSymmetric(TreeNode* root) {
        return (root == nullptr) && check(root->left, root->right);
    }
};