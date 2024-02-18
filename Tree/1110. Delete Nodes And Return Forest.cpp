class Solution {
public:
    TreeNode* helper(TreeNode* root, vector<TreeNode*>& res, unordered_set<int>& to_delete){
        if (!root){
            return root;
        }
        root->left  = helper(root->left, res, to_delete);
        root->right  = helper(root->right, res, to_delete);
        if(to_delete.count(root->val)){
            if(root->left) res.push_back(root->left);
            if(root->right) res.push_back(root->right);
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


class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        queue<pair<TreeNode*, bool>>q;//bool 是parent 是不是delete
        unordered_set<int>st(to_delete.begin(), to_delete.end());
        if (root)
            q.push({root, true});
        vector<TreeNode*>res;
        while(!q.empty()){
            auto [top, parent_delete] = q.front();q.pop();
            //不能用 auto&[top, parent_delete]
            bool is_delete = st.count(top->val);
            
            if(!is_delete && parent_delete){
                res.push_back(top);
            }
            if(top->left){
                auto left = top->left;
                if(st.count(left->val)) 
                    top->left = nullptr;
                q.push({left, is_delete});
            }
            if(top->right){
                auto right = top->right;
                if(st.count(right->val)) 
                    top->right = nullptr;
                q.push({right, is_delete});
            }
        }
        return res;
    }
};

class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        stack<pair<TreeNode*, bool>>q;//bool 是parent 是不是delete
        unordered_set<int>st(to_delete.begin(), to_delete.end());
        if (root)
            q.push({root, true});
        vector<TreeNode*>res;
        while(!q.empty()){
            auto [top, parent_delete] = q.top();q.pop();
            bool is_delete = st.count(top->val);
            
            if(!is_delete && parent_delete){
                res.push_back(top);
            }
            if(top->left){
                auto left = top->left;
                if(st.count(left->val)) 
                    top->left = nullptr;
                q.push({left, is_delete});
            }
            if(top->right){
                auto right = top->right;
                if(st.count(right->val)) 
                    top->right = nullptr;
                q.push({right, is_delete});
            }
        }
        return res;
    }
};