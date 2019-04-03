/*
101. Symmetric Tree
Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree [1,2,2,3,4,4,3] is symmetric:

    1
   / \
  2   2
 / \ / \
3  4 4  3
But the following [1,2,2,null,3,null,3] is not:
    1
   / \
  2   2
   \   \
   3    3
Note:
Bonus points if you could solve it both recursively and iteratively.

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
    bool isSymmetric(TreeNode* root) {
        return !root || helper(root->left, root->right);
    }
    
    bool helper(TreeNode* left, TreeNode* right){
        return !left && !right || (right && left && left->val == right->val) && helper(left->left, right->right) &&   helper(left->right, right->left); 
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
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        stack<TreeNode *>stk;
        stk.push(root->left);
        stk.push(root->right);
        while(!stk.empty()){
            TreeNode* right = stk.top(); stk.pop();
            TreeNode* left = stk.top(); stk.pop();
            if(!left && !right) continue;
            if(!right && left || !left && right || left->val != right->val) return false;
            stk.push(right->left); //as left 
            stk.push(left->right);// as right
            stk.push(left->left);
            stk.push(right->right);
            
        }
        return root;
    }
};



class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        queue<TreeNode*>stk;
        stk.push(root->left);
        stk.push(root->right);
        while(!stk.empty()){
            TreeNode* t1 = stk.front(); stk.pop();
            TreeNode* t2 = stk.front(); stk.pop();
            if(!t1 && t2 || t1 && !t2) return false;
            if(t1 && t2 && t1->val != t2->val) return false;
            if(!t1 && !t2) continue;
            stk.push(t1->left); stk.push(t2->right);
            stk.push(t1->right);stk.push(t2->left);
        }
        return true;
    }
};
