/*
637. Average of Levels in Binary Tree

Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
Note:
The range of node's value is in the range of 32-bit signed integer.

*/

//recursion 
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double>res;
        vector<vector<long>>container;
        helper(root, container, 1);

        for_each(container.begin(),container.end(), [&](auto it){res.push_back(
            accumulate(it.begin(), it.end(), 0.0)/it.size());});
        return res;
    }

    void helper(TreeNode* root, vector<vector<long>>&container, int level){
        if(!root) return;
        if (container.size()<level) container.push_back({root->val});
        else container[level-1].push_back(root->val);
        helper(root->left, container,level+1);
        helper(root->right, container,level+1);
    }
};


//BFS 
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double>res;
        TreeNode *cur = root;
        queue<TreeNode*>q; 
        if(cur)
            q.push(cur);
        int  size = 0;
        while(size = q.size()){
            double sum = 0.0;
            for(int i = 0; i<size; i++){
                TreeNode* cur = q.front(); q.pop();
                sum += cur->val;
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right);
            }
            res.push_back(sum/size);
        }
        return res;
    }
};


//在每一层结束时候，放上nullptr，保证这一层已结束
class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> ret;
        double sum = 0, count = 0;
        queue<TreeNode*> q;
        q.push(root);
        q.push(nullptr);
        while (!q.empty()) {
            TreeNode* t = q.front();
            q.pop();
            if (t == nullptr) {
                ret.push_back(sum / count);
                sum = count = 0;
                if (!q.empty()) q.push(nullptr);
            } else {
                sum += t->val;
                ++count;
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return ret;
    }
};