/*
111. Minimum Depth of Binary Tree

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

Note: A leaf is a node with no children.

Example:

Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7
return its minimum depth = 2.


    3
   / \
  9  20
  /    \
 15     7
return its minimum depth = 3.

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
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        int l = minDepth(root->left);
        int r = minDepth(root->right);
        if(l==0)
            return 1+r;
        if(r==0)
            return 1+l;
        return 1+min(l,r);
    }
};


class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        int L = minDepth(root->left), R = minDepth(root->right);
        return 1 + (min(L, R) ? min(L, R) : max(L, R));
    }

};


class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) return 0;
        if(!root->left &&!root->right) return 1;
        if(!root->right) return 1+minDepth(root->left);
        if(!root->left) return 1+minDepth(root->right);
        return 1 + min(minDepth(root->left), minDepth(root->right));
    }
};



/**
iterative solution 找到那个没有既没有left child 也没有right child的点
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        queue<TreeNode *>q;
        if(root) q.push(root);
        int level = 0;
        while(q.size()){
            int size = q.size();level++;
            for(int i = 0; i<size;i++){
                TreeNode *cur = q.front(); 
                q.pop();
                if(!cur->left && !cur->right) return level;
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
        }
        return level;
    }
};