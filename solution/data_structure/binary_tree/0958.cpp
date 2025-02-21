#include "../include/help.h"


/**
 * @brief 判断是否是一棵完全二叉树, 完全二叉树说的是除了最后一层外,其他层都是满节点的,
 *        最后一层的节点都靠左
 */


class Solution {
public:
    bool isCompleteTree(TreeNode* root) {

        if(root == nullptr) {
            return false;
        }

        queue<TreeNode*> my_queue;
        my_queue.push(root);
        while(!my_queue.empty()) {
            TreeNode* tmp = my_queue.front();
            my_queue.pop();

            if (tmp == nullptr) {
                break;
            }
            else{
                my_queue.push(tmp->left);
                my_queue.push(tmp->right);
            }
        }

        // 判断剩余队列是否有空节点
        while(!my_queue.empty()) {
            TreeNode* tmp = my_queue.front();
            my_queue.pop();
            if (tmp != nullptr) {   // 如果有非空节点说明不是完全二叉树
                return false;
            }
        }

        return true;
    }
};