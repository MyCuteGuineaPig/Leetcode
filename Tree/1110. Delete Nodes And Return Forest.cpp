class Solution {
public:
    TreeNode* helper(TreeNode* root, vector<TreeNode*>& res, unordered_set<int>& to_delete){
        if (!root){
            return root;
        }
        TreeNode* left = helper(root->left, res, to_delete);
        TreeNode* right = helper(root->right, res, to_delete);
        root->left = left;
        root->right = right;
        if(to_delete.count(root->val)){
            if(left) res.push_back(left);
            if(right) res.push_back(right);
            return nullptr;
        }
        return root;
    }

    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int>st(to_delete.begin(), to_delete.end());
        vector<TreeNode*>res;
        root = helper(root, res, st);
        if(root)
            res.push_back(root);
        return res;
    }
};

