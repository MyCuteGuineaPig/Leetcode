/*
144. Binary Tree Preorder Traversal
Given a binary tree, return the preorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,2,3]
Follow up: Recursive solution is trivial, could you do it iteratively?

*/


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        TreeNode *pre = NULL, *cur = root;
        if(!root) return {};
        vector<int>res;
        while(cur){
            if(!cur->left){
                res.push_back(cur->val);
                cur = cur->right;
            }else{
                pre = cur->left;
                while(pre->right && pre->right!=cur)
                    pre = pre->right;
                if(!pre->right){
                    res.push_back(cur->val);
                    pre->right = cur;
                    cur = cur->left;
                }else{ //发现这个current 已经被visit 过了，就不push 进vector
                    pre->right = NULL; 
                    cur = cur->right;
                }
            }
        }
        return res;
    }
};


//stack
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*>stk;
        vector<int>res;
        TreeNode *cur = root;
        while(cur || !stk.empty()){
            if(cur){
                res.push_back(cur->val);
                stk.push(cur->right);
                cur = cur->left;
            }else{//切换到之前的top的右分支
                cur = stk.top();
                stk.pop();
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*>stk;
        vector<int>res;
        TreeNode *cur;
        stk.push(root);
        while(!stk.empty()){
            cur = stk.top();stk.pop();
            if(cur){
                res.push_back(cur->val);
                stk.push(cur->right);
                stk.push(cur->left);
            }
        }
        return res;
    }
};



class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*>rights;
        vector<int>res;
        while(root){
            res.push_back(root->val);
            if(root->right){
                rights.push(root->right);
            }
            root = root->left;
            if(!root && !rights.empty()){
                root = rights.top();
                rights.pop();
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<pair<TreeNode*, bool>>stk;
        vector<int>res;
        stk.push({root,false});
        while(!stk.empty()){
            bool visited;
            tie(root, visited) = stk.top();
            stk.pop();
            if(!root) continue;
            if(visited) res.push_back(root->val);
            else{
                stk.push({root->right, false});
                stk.push({root->left, false});
                stk.push({root, true});
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        TreeNode* pre, *cur;
        stack<TreeNode*>stk;
        cur = root;
        vector<int>res; 
        while(cur){
            res.push_back(cur->val);
            if(cur->left){
                stk.push(cur->left);
            }
            cur = cur->right;
            if(!cur && !stk.empty()){
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
        vector<int> res;
        stack<pair<TreeNode *, bool>> s;
        s.emplace(root, false);
        while (!s.empty()) {
            bool visited;
            tie(root, visited) = s.top();
            s.pop();
            if (root == nullptr) {
                continue;
            }
            if (visited) {
                res.emplace_back(root->val);
            } else {
                s.emplace(root, true);
                s.emplace(root->right, false);
                s.emplace(root->left, false);
            }
        }
        return res;
    }
};