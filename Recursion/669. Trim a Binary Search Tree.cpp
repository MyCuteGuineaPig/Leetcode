/*
669. Trim a Binary Search Tree
>= L). You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.

Example 1:
Input: 
    1
   / \
  0   2

  L = 1
  R = 2

Output: 
    1
      \
       2
Example 2:
Input: 
    3
   / \
  0   4
   \
    2
   /
  1

  L = 1
  R = 3

Output: 
      3
     / 
   2   
  /
 1


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
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        while (root && root->val>R) {  //可能换一次后 又有新问题，所以要重复换
            root = root->left;
            while (root && root->val<L) root = root->right;
        }
        while (root && root->val<L) {
            root = root->right;
            while (root && root->val>R) root = root->left;
        }
        if(root){
            root->left = trimBST(root->left, L,R);
            root->right = trimBST(root->right, L,R);
        }
        return root;
    }
};


class Solution {
public:
    TreeNode* trimBST(TreeNode* root, int L, int R) {
        if(!root) return root;
        if(root->val < L) return trimBST(root->right, L, R);
        else if(root->val > R) return trimBST(root->left, L, R);
        else{
            root->left = trimBST(root->left, L,R);
            root->right = trimBST(root->right, L,R);
            return root;
        }
    }
};