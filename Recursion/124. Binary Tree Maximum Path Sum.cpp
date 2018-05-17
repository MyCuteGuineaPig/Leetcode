/*
124. Binary Tree Maximum Path Sum
Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

Example 1:

Input: [1,2,3]

       1
      / \
     2   3

Output: 6
Example 2:

Input: [-10,9,20,null,null,15,7]

   -10
   / \
  9  20
    /  \
   15   7

Output: 42


*/

/*

  -10                       42                        
   / \                    /   \
  9  20                   9  20+15+7 = 42
    /  \                      / \
   15   7                    15  7
   先找左面的最大的，再找右面最大的，然后结合看是 l大, or r大, or l+root+r 大，or root 大， 再跟max比

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
    int maxPathSum(TreeNode* root) {
        int maxval = numeric_limits<int>::min();
        helper(root,maxval);
        return maxval;
    }
    
    int helper(TreeNode *root, int &maxval){
        if(!root) return 0;
        int left = helper(root->left, maxval);
        int right = helper(root->right,maxval);
        int child = root->val;
        child = max(child, root->val+left);
        child = max(child, root->val+right);
        if(child>maxval) maxval = child;
        if(root->val+left+right>maxval) maxval = root->val+left+right;
        return child;
    }
};


class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int maxval = numeric_limits<int>::min();
        helper(root,maxval);
        return maxval;
    }
    
    int helper(TreeNode *root, int &maxval){
        if(!root) return 0;
        int left = max(0,helper(root->left, maxval));
        int right = max(0,helper(root->right,maxval));
        maxval = max(maxval,left + right + root->val);
        return max(left, right)+root->val;
    }
};



class Solution {
public:
/*    int dfs(TreeNode * root, int & maxSum, list<TreeNode*>&cur, list<TreeNode*>&maxRet) {
        if (!root) return 0;
        
    }
*/
    int dfs(TreeNode*root, int &maxSum) {
        if (!root) return 0;
        int left = dfs(root->left, maxSum);
        int right = dfs(root->right, maxSum);
        maxSum = max({maxSum, root->val, root->val + left, root->val + right, left + right + root->val});
        return max({root->val, root->val + left, root->val + right});
    }
    int maxPathSum(TreeNode* root) {
        int maxSum = INT_MIN;
        dfs(root, maxSum);
        return maxSum;
    }
};