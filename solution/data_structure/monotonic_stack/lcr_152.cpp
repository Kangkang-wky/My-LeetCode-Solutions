#include "../include/help.h"

/**
 * @brief 给定一个后序遍历, 判断其是否为二叉搜索树的后序遍历
 *        Solution1: 递归模拟后序遍历部分
 *        Solution2: 单调栈部分
 */



class Solution1 {
public:
    bool verifyTreeOrder(vector<int>& postorder) {
        return recur(postorder, 0, postorder.size() - 1);
    }
private:
    bool recur(vector<int>& postorder, int i, int j) {
        // post_order 左右根
        if (i >= j) {
            return true;
        }
        // 不断遍历左, 直到碰到比根节点大的部分
        int p = i;
        while(postorder[p] < postorder[j]) {
            p++;
        }
        // 不断遍历右, 直到碰到比根节点小的部分
        int mid = p;
        while(postorder[p] > postorder[j]) {
            p++;
        }
        
        bool flag_left = recur(postorder, i, mid - 1);
        bool flag_right = recur(postorder, mid, j - 1);

        return p == j && flag_left && flag_right;
    }
};

/**
 * @brief 后序遍历检验是否成功
 * 
 */
class Solution2 {
public:
    bool verifyTreeOrder(vector<int>& postorder) {
        stack<int> st;
        int root = std::numeric_limits<int>::max();
        
        // 倒序的顺序是 (根 右 左)
        for(int i = postorder.size() - 1; i >= 0; i--) {
            if (postorder[i] > root) {
                return false;
            }
            while(!st.empty() && st.top() > postorder[i]) {
                root = st.top();
                st.pop();
            }
            st.push(postorder[i]);
        }
        return true;
    }
};