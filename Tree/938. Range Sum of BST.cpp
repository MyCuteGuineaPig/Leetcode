class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        if(!root){return 0;}
        int cur = 0;
        if (root->val >= low && root->val <= high){
            cur += root->val;
        }
        if (root->val >low){
            cur += rangeSumBST(root->left, low, high);
        }
        if (root->val < high){
            cur += rangeSumBST(root->right, low, high);
        }
        return cur;
    }
};


class Solution {
public:
    int rangeSumBST(TreeNode* root, int low, int high) {
        int res = 0;
        queue<TreeNode*>q;
        q.push(root);
        while (!q.empty()){
            int size = q.size();
            for(int a = 0; a < size; ++a){
                auto top = q.front(); q.pop();
                if (top->val >= low && top->val<=high)
                    res += top->val;
                if (top->val >= low && top->left)
                    q.push(top->left);
                if (top->val <= high && top->right)
                    q.push(top->right);   
            }
        }
        return res;
    }
};