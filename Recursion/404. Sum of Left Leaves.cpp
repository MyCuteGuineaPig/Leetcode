/*
404. Sum of Left Leaves

Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7

There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.


*/

/*
BFS
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
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        queue<TreeNode *>q;
        queue<bool>right;
        right.push(true);  //这是防止假如tree只有一个root，没有child，不能算这个点
        if(root) q.push(root); 
        int res = 0;
        while(q.size()){
            int size = q.size();
            for(int i = 0; i<size;i++){
                TreeNode *cur = q.front();q.pop();
                bool isright = right.front();right.pop();
                if(!cur->left && !cur->right && !isright) res+=cur->val;
                if(cur->left) {q.push(cur->left),right.push(false);}
                if(cur->right) {q.push(cur->right); right.push(true);}
            }
        }
        return res;
    }
};



/*
Recursion
 */
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root, bool isleft = false) {
        if(!root) return 0;
        if(!root->left && !root->right && isleft) return root->val;
        return sumOfLeftLeaves(root->left, true) + sumOfLeftLeaves(root->right, false);
    }
};

class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(!root) return 0;
        if(root->left && !root->left->left && !root->left->right)  return root->left->val+sumOfLeftLeaves(root->right);
        return sumOfLeftLeaves(root->left)+sumOfLeftLeaves(root->right);
    }
};