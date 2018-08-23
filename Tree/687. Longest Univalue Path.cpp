/*
687. Longest Univalue Path

Given a binary tree, find the length of the longest path where each node in the path has the same value. This path may or may not pass through the root.

Note: The length of path between two nodes is represented by the number of edges between them.

Example 1:

Input:

              5
             / \
            4   5
           / \   \
          1   1   5
Output:

2
Example 2:

Input:

              1
             / \
            4   5
           / \   \
          4   4   5
Output:

2
Note: The given binary tree has not more than 10000 nodes. The height of the tree is not more than 1000.



*/

class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        int res = 0;
        helper(root, res);
        return res;
    }

    int helper(TreeNode* root, int& res){
        if(!root) return 0;
        int l = helper(root->left, res);
        int r = helper(root->right, res);
        l = root->left && root->left->val == root->val ? l+1: 0;
        r = root->right && root->right->val == root->val ? r+1: 0;
        //cout<<" root "<<root->val<<" left "<<l<<" right "<<r<<endl;
        res = max(res, l+r);
        return max(l, r);
    }
};



class Solution {
public:
    int longestUnivaluePath(TreeNode* root) {
        int res = 0;
        helper(root, res, -1000000000);
        return res;
    }

    int helper(TreeNode* root, int& res, int val){
        if(!root) return 0;
        int l = helper(root->left, res, root->val);
        int r = helper(root->right, res, root->val);
        res = max(res, l+r);
        if(root->val == val) return max(l, r)+1;
        return 0;
    }
};


class Solution {
public:
    int helper(TreeNode* root, int val)
    {
        if(!root || root->val != val) return 0;
        return 1 + max(helper(root->left,val),helper(root->right,val));
    }
    int longestUnivaluePath(TreeNode* root) {
        if(!root) return 0;
        int sub = max(longestUnivaluePath(root->left),longestUnivaluePath(root->right));
        return max(sub,helper(root->left,root->val) + helper(root->right,root->val));
    }
};