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
    unordered_map<int, int> kv{{0,1}};
public:
    int pathSum(TreeNode* root, int sum) {
        return rec(root, 0, sum);
    }
    
    int rec(TreeNode* root, int csum, int targ) {
        if (!root) return 0;
        csum+=root->val;
        kv[csum] += 1;
        int lc = rec(root->left, csum, targ);
        int rc = rec(root->right, csum, targ);
        kv[csum] -= 1;
        return kv[csum-targ] + lc + rc;
    }
};