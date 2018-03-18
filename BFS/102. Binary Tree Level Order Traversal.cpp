/*
102. Binary Tree Level Order Traversal
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        if (root)
            q.push(root);
        vector<vector<int>>res;
        while(q.size()){
            vector<int>temp;
            int cursize = q.size();
            for(int i = 0; i<cursize; i++){
                TreeNode* top = q.front();
                q.pop();
                temp.push_back(top->val);
                if(top->left)
                    q.push(top->left);
                if(top->right)
                    q.push(top->right);
            }
            res.push_back(temp);
        }
        return res;
    }
};
