class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int res = root->val;
        TreeNode* kid = target < res ? root->left: root->right;
        if (!kid) return res;
        int kid_res = closestValue(kid, target);

        if ( abs(kid_res - target) != abs (res - target)) 
            return  abs(kid_res - target) < abs (res - target) ? kid_res : res;
        return min(kid_res, res);
    }
};


class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        int closest = root->val;
        while (root) {
            if (abs(closest - target) >= abs(root->val - target)){
                closest = abs(closest - target) == abs(root->val - target) ? min(root->val, closest): root->val;
            }
            root = target < root->val ? root->left : root->right;
        }
        return closest;
    }
};




class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        int res = numeric_limits<int>::min();
        //不可以是 root->val, 因为比如 [2,1,3]， target = 0.1； root->val  = 2, res = 2 => 错过解
        while (!stk.empty() || cur){
            if (cur) {
                stk.push(cur);
                cur = cur->left;
            } else {
                cur = stk.top(); stk.pop();
                if (res <= target && cur->val > target) {
                    return target - res <= cur->val - target ? res : cur->val;
                }
                res = cur->val;
                cur = cur->right;
            }
        }
        return res;
    }
};



class Solution {
public:
    int closestValue(TreeNode* root, double target) {
        function<void(TreeNode*, double, int&)>  helper = [&](TreeNode* root, double target, int& res){
            if(!root) return;
            if (abs(root->val - target) < abs(res - target) || abs(root->val - target) == abs(res - target) && root->val < res ){
                res = root->val;
            } 
            helper(root->left, target, res);
            helper(root->right, target, res);
        };
        int res = numeric_limits<int>::max();
        helper(root, target, res);
        return res;
    }
};

