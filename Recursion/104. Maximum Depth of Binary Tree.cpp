/*
104. Maximum Depth of Binary Tree
Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its depth = 3.
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
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return 1+max(maxDepth(root->left), maxDepth(root->right));
    }
};

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root==NULL)return 0;
        int left=maxDepth(root->left);
        int right=maxDepth(root->right);
        return max(left,right)+1;
    }
};


/*
BFS 
*/

class Solution {
public:
    int maxDepth(TreeNode* root) {
        queue<TreeNode *>q;
        if(root) q.push(root);
        int h = 0;
        while(q.size()){
            int qsize = q.size(); h++;
            for(int i = 0; i<qsize;i++){
                TreeNode * cur = q.front(); q.pop();
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
        }
        return h;
    }
};