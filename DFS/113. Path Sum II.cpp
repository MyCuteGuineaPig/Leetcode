/*
113. Path Sum II

Time	Space	Difficulty
O(n)	O(h)	Medium

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

For example:
Given the below binary tree and sum = 22,
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
return
[
   [5,4,11,2],
   [5,8,4,5]
]

*/

/*
 * 
 * 需要注意的是helper 待着reference 走，快很多
*/

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>>result;
        helper(root, sum, result, vector<int>() = {});
        return result;
    }
   
    void helper(TreeNode* root, int sum, vector<vector<int>>& result, vector<int>&cur){
        if(!root) {
            return;
        }
        cur.push_back(root->val);
        if(!root->right && !root->left && sum == root->val) {
            result.push_back(cur); 
        }
        helper(root->left, sum - root->val, result, cur);
        helper(root->right,sum - root->val, result, cur);
        cur.pop_back();
    }
};

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>>  res;
        vector<int> temp;
        TreeNode* cur = root, *pre = NULL;
        stack<TreeNode*>stk;
        while(cur || ! stk.empty()){
            if(cur){
                sum -= cur->val;
                stk.push(cur);
                temp.push_back(cur->val);
                cur = cur->left;
            }else{
                cur = stk.top();
                if(!cur->left && !cur->right && sum == 0)
                    res.push_back(temp);
                if(cur->right && pre != cur->right)
                    cur = cur->right;
                else{
                    pre = cur;
                    sum += cur->val;
                    cur = NULL;
                    temp.pop_back();
                    stk.pop();
                }
            }
        }
        return res;
    }
};
