/*
112. Path Sum.cpp

Time	Space	Difficulty
O(n)	O(h)	Easy

Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \      \
        7    2      1
return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.

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
    bool hasPathSum(TreeNode* root, int sum, int checksum = 0) {
        if(!root) return false;
        return !root->left && !root->right ? checksum+root->val == sum : (hasPathSum(root->left, sum, checksum+root->val) ||hasPathSum(root->right, sum, checksum+root->val));
    }
};

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        
        return !root->left && !root->right ? sum == root->val : hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);
        
    }
};

//iterative
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        stack<TreeNode*>stk;
        while(root || !stk.empty()){
            if(root){
                stk.push(root);
                if(root->left)
                    root->left->val += root->val;
                else if(!root->right && root->val == sum)
                    return true;
                root = root->left;       
            }else{
                root = stk.top(); stk.pop();
                if(root->right)
                    root->right->val += root->val;
                root = root->right;
            }
        }
        return false;
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
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        stack<TreeNode *>stk;
        int check = 0; 
        TreeNode *pre = NULL, *cur = root;
        while(cur || !stk.empty()){
            while(cur){  //尽可能到最左面
                check += cur->val;
                stk.push(cur);  
                cur = cur->left;
            }
            cur = stk.top();
            if(!cur->left && !cur->right && check == sum){
                return true;
            }
            if(cur->right && pre != cur->right){  //右侧有child, 到右侧
                cur = cur->right;
            }else{
                pre = cur;
                check -= cur->val;  //往上走
                stk.pop();
                cur = NULL;
            }
            
        }
        return false;
    }
};
