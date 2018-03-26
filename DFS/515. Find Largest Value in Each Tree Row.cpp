/*
515. Find Largest Value in Each Tree Row
You need to find the largest value in each row of a binary tree.

Time	Space	Difficulty	
O(n)	O(h)	Medium
Example:
Input: 

          1
         / \
        3   2
       / \   \  
      5   3   9 

Output: [1, 3, 9]
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
    vector<int> largestValues(TreeNode* root) {
        vector<int>res;
        dfs(root, 1, res);
        return res;
    }
    
    void dfs(TreeNode* root, int level,vector<int>&res ){
        if(!root) return;
        if(res.size()<level)
            res.push_back(root->val);
        else
            res[level-1] = max( res[level-1],root->val);
        dfs(root->left, level+1, res);
        dfs(root->right, level +1, res);
    }
};

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
    vector<int> largestValues(TreeNode* root) {
        vector<int>res;
        queue<TreeNode *>q;
        if(root){
            q.push(root); q.push(NULL);
        }
        int maxnum = INT_MIN;
        while(q.size()){
            TreeNode *top = q.front();
            q.pop();
            if(top){
                maxnum = max(maxnum, top->val);
                if(top->left) q.push(top->left);
                if(top->right) q.push(top->right);
            }
            else{
                res.push_back(maxnum);
                maxnum = INT_MIN;
                if(q.size())
                    q.push(NULL);
            }
            
            
        }
        return res;
    }
};