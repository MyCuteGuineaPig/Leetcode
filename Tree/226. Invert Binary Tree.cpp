/*
226. Invert Binary Tree

Invert a binary tree.

Example:

Input:

     4
   /   \
  2     7
 / \   / \
1   3 6   9
Output:

     4
   /   \
  7     2
 / \   / \
9   6 3   1


*/


class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root) {
            swap(root->left, root->right);
            invertTree(root->left);
            invertTree(root->right);
        }
        return root;
    }
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root) {
            TreeNode* tmp = root->left;
            root->left = invertTree(root->right);
            root->right = invertTree(tmp);
            
        }
        return root;
    }
};

//DFS
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return root;
        stack<TreeNode*>stk;
        stk.push(root);
        while(!stk.empty()){
            TreeNode* cur = stk.top();
            stk.pop();
            swap(cur->left, cur->right);
            if(cur->left) stk.push(cur->left);
            if(cur->right) stk.push(cur->right);
        }
        return root;
    }
};

//BFS,// Space: O(w), w is the max number of nodes of the levels.
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return root;
        queue<TreeNode*>stk;
        stk.push(root);
        while(!stk.empty()){
            TreeNode* cur = stk.front();
            stk.pop();
            swap(cur->left, cur->right);
            if(cur->left) stk.push(cur->left);
            if(cur->right) stk.push(cur->right);
        }
        return root;
    }
};