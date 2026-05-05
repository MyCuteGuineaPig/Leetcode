/*
437. Path Sum III

You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11


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
    int pathSum(TreeNode* root, int sum) {
        return helper(root,sum,{});
    }
    
    int helper(TreeNode *root, const int& target, vector<int>sum){
        if(!root) return 0;
        int cur = 0;
        if(root->val == target) cur++;
        for(auto &i:sum){
            if(i+root->val==target) cur++;
            i = i+root->val;
        }
        sum.push_back(root->val);
        int l = helper(root->left, target,sum);
        int r = helper(root->right, target,sum);
        return cur+l+r;
    }
};


class Solution {
public:
    unordered_map<int, int>pairs;
    int pathSum(TreeNode* root, int target, int totalsum = 0) {
        if(!root) return 0;
        totalsum += root->val;
        int res = (totalsum == target ? 1 : 0 ) + (pairs.count(totalsum - target) ? pairs[totalsum - target] : 0);
        pairs[totalsum] += 1;
        res += pathSum(root->left, target, totalsum) + pathSum(root->right, target, totalsum);
        pairs[totalsum] -= 1;
        if(pairs[totalsum] == 0) pairs.erase(totalsum);
        return res;
    }
};


class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long, int>mp;
        mp[0] = 1;
        auto dfs = [&](this auto && dfs, TreeNode* cur, long cursum) {
            if(!cur) return 0;
            cursum += cur->val;
            mp[cursum] += 1;
            int l = dfs(cur->left, cursum);
            int r = dfs(cur->right, cursum);
            mp[cursum] -= 1;
            
            return  mp[cursum - targetSum] + l + r;
        };  
        return dfs(root, 0);
    }
};



class Solution {
public:
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long, int>mp;
        mp[0] = 1;
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        TreeNode* prev = nullptr;
        long cursum = 0;
        int res = 0;
        while (cur || !stk.empty()) {
            if(cur) {
                stk.push(cur);

                cursum += cur->val;
                res += mp[cursum - targetSum];
                mp[cursum]++;
                
                cur = cur->left;
            } else {
                cur = stk.top();

                if(cur->right && cur->right != prev) {
                    cur = cur->right;
                } else {
                    mp[cursum] -= 1;  //表示right 已经visit过，需要pop node return to parents
                    cursum -= cur->val; 

                    stk.pop();
                    prev = cur;
                    cur = nullptr;
                }
            }
        }
        return res;
    }
};