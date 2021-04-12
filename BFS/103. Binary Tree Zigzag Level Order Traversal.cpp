/*
103. Binary Tree Zigzag Level Order Traversal
Time	Space	Difficulty
O(n)	O(n)	Medium

Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its zigzag level order traversal as:
[
  [3],
  [20,9],
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        if(root)
            q.push(root);
        vector<vector<int>>res;
        int count = 0;
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
            if(count++ & 1 == 1)
                reverse(temp.begin(),temp.end());
            res.push_back(temp);
        }
        return res;
    }
};



class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>>res;
        build(res, 0, root);
        for(int i = 0; i<res.size(); ++i)
            if(i & 1)
                reverse(res[i].begin(), res[i].end());
        return res;
    }
    
    void build(vector<vector<int>>&res, int l, TreeNode* cur){
        if(!cur)
            return;
        if(res.size() <= l)
            res.push_back({});
        res[l].push_back(cur->val);
        build(res, l+1, cur->left);
        build(res, l+1, cur->right);
    }
};