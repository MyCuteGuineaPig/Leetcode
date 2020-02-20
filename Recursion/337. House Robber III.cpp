/*
337. House Robber III
The thief has found himself a new place for his thievery again. 
There is only one entrance to this area, called the "root." 
Besides the root, each house has one and only one parent house.
 After a tour, the smart thief realized that "all houses in this place forms a binary tree". 
 It will automatically contact the police if two directly-linked houses were broken into on the same night.

Determine the maximum amount of money the thief can rob tonight without alerting the police.

Example 1:
     3
    / \
   2   3
    \   \ 
     3   1
Maximum amount of money the thief can rob = 3 + 3 + 1 = 7.
Example 2:
     3
    / \
   4   5
  / \   \ 
 1   3   1
Maximum amount of money the thief can rob = 4 + 5 = 9.

*/


class Solution {
public:
    pair<int,int>helper(TreeNode* root){ //first last, second last two
        if(!root) return {0,0};
        pair<int,int>l = helper(root->left);
        pair<int,int>r = helper(root->right);
        return {max(l.second + r.second + root->val, l.first + r.first), l.first + r.first };
        //first 用上root的最大值,
        //second, 不用现在root的
    }
    
    int rob(TreeNode* root) {
        return helper(root).first;
    }
};

/*
返回一个vector, vector 第一个存的是用上一个最大的获取值，第二个存的是不用上一个 最大的获取值
*/

class Solution {
public:
    int rob(TreeNode* root) {
        vector<int> res = helper(root);
        return max(res[0],res[1]);
    }

    vector<int> helper(TreeNode* root){ //first is count current element + sum(left child) + sum(right child), second is left + right
        if(!root) return {0,0};
        vector<int>left = helper(root->left);
        vector<int>right = helper(root->right);
        //cout<<" root "<<root->val<<" left0 "<<left[0]<<" right0 "<<right[0]<<" left1 "<<left[1]<<" right1 "<<right[1]<<endl;
        return {left[1]+root->val+right[1],max(left[0],left[1])+max(right[0],right[1])};
    }
};
