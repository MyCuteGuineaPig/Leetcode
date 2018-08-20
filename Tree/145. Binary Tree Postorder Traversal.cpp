/*
145. Binary Tree Postorder Traversal
Given a binary tree, return the postorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [3,2,1]
Follow up: Recursive solution is trivial, could you do it iteratively?

*/



//Morris Traversal 先去 右侧的，再去左侧的，push的顺序与preorder一样，就是最后需要reverse res
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        TreeNode* pre, *cur;
        if(!root) return {};
        cur = root;
        vector<int>res;
        while(cur){
            if(!cur->right){
                res.push_back(cur->val);
                cur = cur->left;
            }else{
                pre = cur->right;
                while(pre->left && pre->left!=cur)
                    pre = pre->left;
                if(!pre->left){
                    res.push_back(cur->val);
                    pre->left = cur;
                    cur = cur->right;
                }else{
                    pre->left = NULL;
                    cur = cur->left;
                }
            }
        }
        reverse(res.begin(),res.end());
        return res;
    }
};


//stack 
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        TreeNode* pre, *cur;
        stack<TreeNode*>stk;
        cur = root;
        vector<int>res;
        while(cur || !stk.empty()){
            if(cur){
                res.push_back(cur->val);
                stk.push(cur->left);
                cur = cur->right;
            }else{
                cur = stk.top();
                stk.pop();
            }
        }
        reverse(res.begin(),res.end());
        return res;
    }
};


class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        TreeNode* pre, *cur;
        stack<TreeNode*>stk;
        cur = root;
        stk.push(cur);
        vector<int>res; 
        while(!stk.empty()){
            cur = stk.top(); stk.pop();
            if(cur){
                res.push_back(cur->val);
                stk.push(cur->left);
                stk.push(cur->right);
            }
        }
        reverse(res.begin(),res.end());
        return res;
    }
};