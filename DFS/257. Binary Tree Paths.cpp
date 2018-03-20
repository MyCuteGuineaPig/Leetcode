/*
257. Binary Tree Paths

Time	Space	Difficulty
O(n * h)	O(h)	Easy	

Given a binary tree, return all root-to-leaf paths.

For example, given the following binary tree:

   1
 /   \
2     3
 \
  5
All root-to-leaf paths are:

["1->2->5", "1->3"]

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

//*注意必须是左child 和 右 child 同时都没有才能说这是path，如果一个点有右child，没有左child，不能说有

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string>res;
        if(!root) return res;
        helper(root, res, to_string(root->val));
        return res;
    }

    void helper(TreeNode* root, vector<string>& res, string cs){
        if(!root->left && !root->right) res.push_back(cs);
        if(root->left)
            helper(root->left, res, cs+"->"+to_string(root->left->val));
        if(root->right)
            helper(root->right, res, cs+"->"+to_string(root->right->val));
    }
};


// 这个方法更快，因为pass reference without 每次都复制string，然后intialize

class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string>res;
        vector<int>pt;
        if(!root) return res;
        helper(root, res, pt);
        return res;
    }

    void helper(TreeNode* root, vector<string>& res, vector<int>& pt){
        pt.push_back(root->val);
        if(!root->left && !root->right) {
            string cs; 
            for(int i = 0; i<pt.size();i++){
                cs += to_string(pt[i]);
                if(i<pt.size()-1) cs+= "->";
            }
            res.push_back(cs);
        }
        if(root->left)
            helper(root->left, res, pt);
        if(root->right)
            helper(root->right, res, pt);
        pt.pop_back();
    }
};