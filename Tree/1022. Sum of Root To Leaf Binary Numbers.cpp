class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        auto dfs = [&](this auto&& dfs, TreeNode* cur, int sum) {
            if(!cur) return sum;
            sum = (sum << 1) + cur->val;
            if(!cur->left && !cur->right) return sum;

            int left = cur->left ?  dfs(cur->left, sum): 0;
            
            int right = cur->right ?  dfs(cur->right, sum): 0;

            return left + right;
        };

        return dfs(root, 0);
    }
};



class Solution {
public:
    int sumRootToLeaf(TreeNode* root) {
        int res = 0;
        auto dfs = [&](this auto&& dfs, TreeNode* cur, int sum) -> void {
            if (!cur) return;
            sum = (sum << 1) + cur->val;
            if(!cur->left && !cur->right) {
                res += sum;
                return;
            }
            dfs(cur->left, sum);
            dfs(cur->right, sum);

            return;
        };
        dfs(root, 0);
        return res;
    }
};