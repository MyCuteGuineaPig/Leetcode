/*
543. Diameter of Binary Tree

Given a binary tree, you need to compute the length of the diameter of the tree. 
The diameter of a binary tree is the length of the longest path between any two nodes in a tree. 
This path may or may not pass through the root.

Example:
Given a binary tree 
          1
         / \
        2   3
       / \     
      4   5    
Return 3, which is the length of the path [4,2,1,3] or [5,2,1,3].

Note: The length of path between two nodes is represented by the number of edges between them.



*/

/*

tree 可能是这样比如 

        1
      /    \ 
     1     2
        /   \
       3     5
     /        \ 
    4        6
*/


class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        return !root ? 0 : max(max(maxdepth(root->left) + maxdepth(root->right), diameterOfBinaryTree(root->left)), diameterOfBinaryTree(root->right));
    }
    
    int maxdepth(TreeNode* root){
        return !root ? 0: 1+max(maxdepth(root->left),maxdepth(root->right));
    }
};

//更快
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        depth(root, &diameter);
        return diameter;
    }

private:
    int depth(TreeNode *root, int *diameter) {
        if (!root) {
            return 0;
        }
        auto left = depth(root->left, diameter);
        auto right = depth(root->right, diameter);
        *diameter = max(*diameter, left + right);
        return 1 + max(left, right);
    }
};