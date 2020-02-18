/*
110. Balanced Binary Tree

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example 1:

Given the following tree [3,9,20,null,null,15,7]:

    3
   / \
  9  20
    /  \
   15   7
Return true.

Example 2:

Given the following tree [1,2,2,3,3,null,null,4,4]:

       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
Return false.

*/



/*
1. Bottom-up Approach Complexity O(N)
*/
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return height(root)!=-1;
    }
    
    int height(TreeNode *root){
        if(!root) return 0;
        int l = height(root->left);
        if(l==-1) return -1;
        int r = height(root->right);
        if(r == -1) return -1;
        if(abs(l-r)>1) return -1;
        return max(l,r)+1;
    }
};



class Solution {
public:
    int height(TreeNode* root){
        if(!root) return 0;
        int left = height(root->left);
        int right = height(root->right);
        if(left ==-1 || right == -1 || abs(left-right)>1)
            return -1;
        return max(left, right)+1;
    }
    
    bool isBalanced(TreeNode* root) {
        return height(root) != -1;
    }
};


/*
2. Top down approach.  the overall complexity of isBalanced will be O(N^2)
*/

class Solution {
public:
    int depth (TreeNode *root) {
        if (root == NULL) return 0;
        return max (depth(root -> left), depth (root -> right)) + 1;
    }

    bool isBalanced (TreeNode *root) {
        if (root == NULL) return true;
        
        int left=depth(root->left);
        int right=depth(root->right);
        
        return abs(left - right) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
};
