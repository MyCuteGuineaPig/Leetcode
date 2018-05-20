/*
671. Second Minimum Node In a Binary Tree

Given a non-empty special binary tree consisting of nodes with the non-negative value, 
where each node in this tree has exactly two or zero sub-node. If the node has two sub-nodes, 
then this node's value is the smaller value among its two sub-nodes.

Given such a binary tree, you need to output the second minimum value in the set made of all the nodes' value in the whole tree.

If no such second minimum value exists, output -1 instead.

Example 1:
Input: 
    2
   / \
  2   5
     / \
    5   7

Output: 5
Explanation: The smallest value is 2, the second smallest value is 5.
Example 2:
Input: 
    2
   / \
  2   2

Output: -1
Explanation: The smallest value is 2, but there isn't any second smallest value.

*/



class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        if(!root || !root->left) return -1;
        int s2 = numeric_limits<int>::max(), rval = root->val;
        helper(root, s2,rval);
        return s2 == numeric_limits<int>::max() ? -1 : s2;
    }
    
    void helper(TreeNode* root, int & s2, const int & rval){
        if(!root) return;
        if(root->val>rval) {
            s2 = min(s2,root->val);
        }
        helper(root->left, s2, rval);
        helper(root->right, s2,rval);
    }
};

class Solution {
public:
    int findSecondMinimumValue(TreeNode* root) {
        if(!root || !root->left) return -1;
        int rval = root->val;
        return helper(root,rval);
    }
    
    int helper(TreeNode* root, const int & rval){
        if(!root) return -1;
        if(root->val!=rval) return root->val;
        int left = helper(root->left, rval), right = helper(root->right,rval);
        if(left == -1) return right;
        if(right == -1) return left;
        return min(left, right);
    }
};


class Solution {
public:
    int SecondMin(TreeNode const * root, int min_val) {
        if (!root) return INT_MAX;
        if (root->val != min_val) return root->val;
        return min(SecondMin(root->left, min_val), SecondMin(root->right, min_val));
    }
    int findSecondMinimumValue(TreeNode* root) {
        if (!root) return -1;
        int sec_min = SecondMin(root, root->val);
        return sec_min == INT_MAX ? -1 : sec_min;
    }
};