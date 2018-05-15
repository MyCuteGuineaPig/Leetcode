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

For the current node root, calling depth() for its left and right children actually has to access all of its children, 
thus the complexity is O(N). We do this for each node in the tree, so the overall complexity of isBalanced will be O(N^2). 
This is a top down approach.
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

/*
2.The second method is based on DFS. Instead of calling depth() explicitly for each child node, 
we return the height of the current node in DFS recursion. 
When the sub tree of the current node (inclusive) is balanced,
 the function dfsHeight() returns a non-negative value as the height. 
 Otherwise -1 is returned. According to the leftHeight and rightHeight of the two children, 
 the parent node could check if the sub tree
is balanced, and decides its return value.

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
    bool isBalanced(TreeNode* root) {
        if (helper(root) == -1)
            return false;
        return true;
    }
    
    int helper(TreeNode* root) {
        if (root == nullptr)
            return 0;
        cout<<" root->val to l "<<root->val<<endl;
        int left = helper(root->left);
        cout<<" root->val left "<<root->val<<" left "<<left<<endl;
        if (left == -1)
            return -1;
        cout<<" root->val to r "<<root->val<<endl;
        int right = helper(root->right);
        cout<<" root->val right "<<root->val<<" left "<<left<<" right "<<right<<endl;
        if (right == -1)
            return -1;
        if (abs(left - right) <= 1){
            cout<<" root->val return "<<root->val<<" max(left, right) + 1; "<<max(left, right) + 1<<endl;
            return max(left, right) + 1;
        }
        return -1;
    }
};