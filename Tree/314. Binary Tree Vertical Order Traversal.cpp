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
    int count_left(TreeNode* root){
        if(!root){
            return -1;
        }
        int left_count = count_left(root->left) + 1;
        int right_count = count_left(root->right) - 1;
        //cout<<"root->val"<<root->val<<" left "<<left_count<<" right "<<right_count<<endl;
        return max(left_count, right_count);
    }

    vector<vector<int>> verticalOrder(TreeNode* root) {
        if(!root) return {};
        int left_count = count_left(root);
        vector<vector<int>>res(left_count+1);
        queue<pair<TreeNode*,int>>q; 
        q.push({root, left_count});
        while(!q.empty()){
            int size = q.size();
            for(int a = 0 ; a < size; ++a){
                auto [cur, level] = q.front(); q.pop();
                if(level >= res.size()) {
                    res.push_back({});
                }
                res[level].push_back(cur->val);
                if(cur->left){
                    q.push({cur->left, level-1});
                }
                if (cur->right){
                    q.push({cur->right, level+1});
                }
            }
        }
        return res;
    }
};