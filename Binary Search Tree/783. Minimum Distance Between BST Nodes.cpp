/*
783. Minimum Distance Between BST Nodes

Given a Binary Search Tree (BST) with the root node root, 
return the minimum difference between the values of any two different nodes in the tree.

Example :

Input: root = [4,2,6,1,3,null,null]
Output: 1
Explanation:
Note that root is a TreeNode object, not an array.

The given tree [4,2,6,1,3,null,null] is represented by the following diagram:

          4
        /   \
      2      6
     / \    
    1   3  

while the minimum difference in this tree is 1, it occurs between node 1 and node 2, 
also between node 3 and node 2.
Note:

The size of the BST will be between 2 and 100.
The BST is always valid, each node's value is an integer, and each node's value is different.

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
    int minDiffInBST(TreeNode* root) {
        int res = numeric_limits<int>::max();
        helper(root,numeric_limits<int>::min(),numeric_limits<int>::max(),res);
        return res;
    }
    
    void helper(TreeNode* root, int minval, int maxval, int &res){
        if(root){
            if(minval!=numeric_limits<int>::min())
                res = min(res, root->val-minval);
            if(minval!=numeric_limits<int>::max())
                res = min(res, maxval-root->val);
            helper(root->left,minval,root->val,res);
            helper(root->right,root->val,maxval,res);
        }
        
    }
};


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
    int minDiffInBST(TreeNode* root) {
        int res = numeric_limits<int>::max(), prev =  numeric_limits<int>::min();
        helper(root,prev,res);
        return res;
    }
    
    void helper(TreeNode* root, int &prev, int &res){
        if(root){
            helper(root->left,prev,res);
            if(prev!=numeric_limits<int>::min())
                res = min(res, root->val-prev);
            prev = root->val;
            helper(root->right,prev,res);
        }
        
    }
};



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
    int minDiffInBST(TreeNode* root) {
        int res = numeric_limits<int>::max();
        TreeNode *prev = nullptr;
        helper(root,prev,res);
        return res;
    }
    
    void helper(TreeNode* root, TreeNode* &prev, int &res){
        if(root){
            helper(root->left,prev,res);
            if(prev!=nullptr)
                res = min(res, root->val-prev->val);
            prev = root;
            helper(root->right,prev,res);
        }
        
    }
};



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
    int minDiffInBST(TreeNode* root) {
        stack<TreeNode *>stk;
        int topval = root->val, prev = numeric_limits<int>::min(), res = numeric_limits<int>::max();
        bool hit = false;
        stk.push(root);
        while(stk.size()){
            if(root){
                stk.push(root);
                root = root->left;
            }else{
                root = stk.top();
                stk.pop();
                if(prev!=numeric_limits<int>::min() && (!hit || root->val!=topval))
                    res = min(res, root->val-prev);
                if(!hit && root->val==topval)
                    hit = true;
                prev = root->val;
                root = root->right;
            }
        }
        return res;
    }
};