#include "../include/help.h"

class Solution {
public:
vector<int> inorderTraversal(TreeNode* root) 
    {
        vector<int>v;
        stack<TreeNode*> st;
        TreeNode* cur=root;
        while(cur || st.size()!=0)
        {
            //左路节点
            while(cur)
            {
                st.push(cur);
                cur=cur->left;
            }
            //取栈顶
            TreeNode*stop=st.top();
            //栈里面取到一个节点时，一定是它的左子树访问完了
             v.push_back(stop->val);
            st.pop();
            //左路节点1的右子树
            cur=stop->right;
        }
        return v;
    }
};