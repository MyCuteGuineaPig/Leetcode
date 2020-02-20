/*
199. Binary Tree Right Side View

Time	Space	Difficulty
O(n)	O(h)	Medium

Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

For example:
Given the following binary tree,
   1            <---
 /   \
2     3         <---
 \     \
  5     4       <---
You should return [1, 3, 4].

Credits:
Special thanks to @amrsaqr for adding this problem and creating all test cases.




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


//BFS
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int>res;
        queue<TreeNode*> q;
        if(root)
            q.push(root);
        while(q.size()){
            int cursize = q.size();
            for(int i = 0; i<cursize; i++){
                TreeNode *top = q.front();
                q.pop();
                if(i == cursize -1) res.push_back(top->val);
                if(top->left) q.push(top->left);
                if(top->right) q.push(top->right);
            }
        }
        return res;
    }
};


class Solution {
public:
    void helper(TreeNode* root, vector<int>&view, int h){
        if(!root) return;
        if(h == view.size()) view.push_back(root->val);
        else view[h] = root->val;
        helper(root->left, view, h+1);
        helper(root->right, view, h+1);
    }
    
    vector<int> rightSideView(TreeNode* root) {
        vector<int>view;
        helper(root, view, 0);
        return view;
    }
};

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int>res;
        if(!root)
            return res;
        helper(root,1,res);
        return res;
    }

    void helper(TreeNode* root, int level, vector<int>&res){
        if(root){
            if(res.size()< level) res.push_back(root->val);
            helper(root->right,level+1, res);
            helper(root->left,level+1, res);
        }
    }
};


class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        if(!root) return res;
        int end = root->val;
        queue<TreeNode*> q;
        q.push(root);
        q.push(NULL);
        
        while(!q.empty()){
            TreeNode* temp = q.front();
            q.pop();
            if(!temp){
                //cout<<"insert "<<end<<endl;
                res.push_back(end);
                if(!q.empty()){
                    q.push(NULL);
                }
            }
            else{
                //cout<<"push "<<temp->val<<endl;
                end = temp->val;
                if(temp->left) q.push(temp->left);
                if(temp->right) q.push(temp->right);
            }
        }
        
        return res;
    }
};
