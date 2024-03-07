/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    pair<int, int> helper(TreeNode* root, int& cnt){
        if(!root) return {0, 0};
        auto left = helper(root->left, cnt);
        auto right = helper(root->right, cnt);
        if( (left.first + right.first + root->val)/ (left.second + right.second + 1) == root->val){
            ++cnt;
        }
        return {left.first + right.first + root->val, left.second + right.second+1};
    }

    int averageOfSubtree(TreeNode* root) {
        int cnt = 0;
        helper(root, cnt);
        return cnt;
    }
};

class Solution {
public:
    array<int, 3> dfs(TreeNode* n) {
        if (n == nullptr)
            return {0, 0, 0};
        auto p1 = dfs(n->left), p2 = dfs(n->right);
        int sum = p1[0] + p2[0] + n->val, count = 1 + p1[1] + p2[1];
        return {sum, count, p1[2] + p2[2] + (n->val == sum / count)};
    }
    int averageOfSubtree(TreeNode* root) {
        return dfs(root)[2];
    }
};