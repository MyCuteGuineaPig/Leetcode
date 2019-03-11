/*
129. Sum Root to Leaf Numbers

Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path 1->2->3 which represents the number 123.

Find the total sum of all root-to-leaf numbers.

Note: A leaf is a node with no children.

Example:

Input: [1,2,3]
    1
   / \
  2   3
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.
Example 2:

Input: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.


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
    int sumNumbers(TreeNode* root) {
        vector<int>tree;
        if (root)
            helper(root, 0, tree);
        return accumulate(tree.begin(),tree.end(),0);
    }
    
    void helper(TreeNode *root, int prev, vector<int>&tree){
        if(!root->left && !root->right) tree.push_back(prev*10+root->val);
        if(root->left)
            helper(root->left, prev*10+root->val, tree);
        if(root->right)
            helper(root->right, prev*10+root->val, tree);
    }
};



class Solution {
public:
    int sumNumbers(TreeNode* root) {
        int res = 0;
        if (root)
            helper(root, 0, res);
        return res;
    }
    
    void helper(TreeNode *root, int prev, int &res){
        prev = prev*10+root->val;
        if(!root->left && !root->right) res+=prev;
        if(root->left)
            helper(root->left, prev, res);
        if(root->right)
            helper(root->right, prev, res);
    }
};


class Solution {
public:
    int sumNumbers(TreeNode* root) {
        return helper(root, 0);
    }
    
    int helper(TreeNode *root, int prev){
        if(!root) return 0;
        prev = prev*10+root->val;
        if(!root->left && !root->right) return prev;
        return helper(root->left, prev)+helper(root->right, prev);
    }
};


/*
BFS solution, change tree internal
*/
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        queue<TreeNode*> q;
        if(root) q.push(root);
        int res = 0;
        while(q.size()){
            int size = q.size();
            for(int i = 0; i<size; i++){
                TreeNode *top = q.front(); q.pop();
                if(!top->left && !top->right) res+=top->val;
                if(top->left){
                    top->left->val += top->val*10;
                    q.push(top->left);
                }
                if(top->right){
                    top->right->val += top->val*10;
                    q.push(top->right);
                }
            }
        }
        return res;
    }
};

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if(!root) return 0;
        stack<TreeNode*> stk;
        TreeNode* cur = root;
        int sum = 0;
        while(cur || !stk.empty()){
            if(cur){
                stk.push(cur);
                if(cur->left) 
                    cur->left->val = cur->val*10 + cur->left->val;
                else if(!cur->right)
                    sum += cur->val;
                cur = cur->left;
            }else{
                cur = stk.top(); stk.pop();
                if(cur->right)
                    cur->right->val = cur->val*10 +cur->right->val;
                cur = cur->right;
            }
        }
        return sum;
    }
    
};
