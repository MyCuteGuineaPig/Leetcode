/*
530. Minimum Absolute Difference in BST

Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.

Example:

Input:

   1
    \
     3
    /
   2

Output:
1

Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
Note: There are at least two nodes in this BST.



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
    int getMinimumDifference(TreeNode* root) {
        long minmin = INT_MAX;
        helper(root, numeric_limits<int>::min(),numeric_limits<int>::max(), minmin);
        return minmin;
    }
    
    void helper(TreeNode* root, long maxval, long minval, long &minmin){
        if(root){
            //cout<<root->val<<" min "<<minval<<" max "<<maxval<<endl;
            minmin = min(abs(root->val - maxval),minmin);
            minmin = min(abs(root->val - minval),minmin);
            //cout<<" abs(root->val - minval) "<<abs(root->val - minval)<<endl;
            helper(root->left, root->val, minval, minmin);
            helper(root->right, maxval, root->val,minmin);
        }
    }
};


/*

Inorder Traversal: 带着prev
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
    int getMinimumDifference(TreeNode* root) {
        int prev = numeric_limits<int>::min();
        int result = numeric_limits<int>::max();
        dfs(root, prev, result);
        return result;
    }

private:
    void dfs(TreeNode* root, int& prev, int& result) {
        if(!root) return;
        dfs(root->left, prev, result);
        if(prev!=numeric_limits<int>::min())
            result = min(result, root->val - prev);
        prev = root->val;
        dfs(root->right, prev, result);
    }
};

/*
Inorder Traversal: 带着prev的root
*/
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        TreeNode *prev = nullptr;
        int result = numeric_limits<int>::max();
        dfs(root, prev, result);
        return result;
    }

private:
    void dfs(TreeNode* root, TreeNode* &prev, int& result) {
        if(!root) return;
        dfs(root->left, prev, result);
        if(prev!=nullptr)
            result = min(result, root->val - prev->val);
       
        prev = root;
        dfs(root->right, prev, result);
    }
};