/*
538. Convert BST to Greater Tree

Given a Binary Search Tree (BST), 
convert it to a Greater Tree such that every key of the original BST is changed to the original key plus sum of all keys greater than the original key in BST.

Example:

Input: The root of a Binary Search Tree like this:
              5
            /   \
           2     13

Output: The root of a Greater Tree like this:
             18
            /   \
          20     13


*/



class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        int presum = 0;
        Helper(root, presum);
        return root;
    }
    
    void Helper(TreeNode* root, int& presum){
        if(!root) return;
        Helper(root->right, presum);
        root->val += presum;
        presum = root->val;
        Helper(root->left, presum);
    }
};


class Solution {
    int helper(TreeNode* root, int gs) {
        if(!root) return gs;
        root->val += helper(root->right, gs);
        return helper(root->left, root->val);
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        helper(root,0);
        return root;
    }
};

//Morris Traversal
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        int presum = 0;
        TreeNode* cur = root;
        while(cur){
            if(!cur->right){
                cur->val += presum;
                presum = cur->val;
                cur = cur->left;
            }else{
                TreeNode* pre = cur->right;
                while(pre->left && pre->left != cur)
                    pre = pre->left;
                if(!pre->left){
                    pre->left = cur;
                    cur = cur->right;
                }else{
                    cur->val += presum;
                    presum = cur->val;
                    cur = cur->left;
                    pre->left = NULL;
                }
            }
            
        }
        return root;
    }
};