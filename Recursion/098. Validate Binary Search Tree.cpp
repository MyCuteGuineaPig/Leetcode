/*

98. Validate Binary Search Tree
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than the node's key.
Both the left and right subtrees must also be binary search trees.
Example 1:

Input:
    2
   / \
  1   3
Output: true
Example 2:

    5
   / \
  1   4
     / \
    3   6
Output: false
Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
             is 5 but its right child's value is 4.
*/



/*
limit用long, 否则比不出来，因为test case有INT_MIN, INT_MAX


If we use in-order traversal to serialize a binary search tree, we can
get a list of values in ascending order. It can be proved with the
definition of BST. And here I use the reference of TreeNode
pointer prev as a global variable to mark the address of previous node in the
list.

“In-order Traversal”:
https://en.wikipedia.org/wiki/Tree_traversal#In-order
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
    bool isValidBST(TreeNode* root,long maxval = numeric_limits<long>::max(), long minval = numeric_limits<long>::min()) {
        if(!root) return true;
        if(root->val<=minval || root->val>=maxval) return false;
        return isValidBST(root->left, root->val, minval) && isValidBST(root->right, maxval, root->val) ;
    }
};



class Solution {
public:
    bool isValidBST(TreeNode* root) {
        TreeNode *prev = nullptr;
        return helper(root,prev);
    }
    
    bool helper(TreeNode* root, TreeNode *&prev){
        if(!root) return true;
        if(!helper(root->left,prev)) {
            //cout<<" false "<<root->val<<" left "<<endl;
            return false;
        }
        if(prev!= nullptr && root->val <=prev->val) {
            //cout<<"cur root "<<root->val<<" prev "<<prev->val<<endl;
            return false;
        }
        prev = root;
        //cout<<"cur root "<<root->val<<endl;
        return helper(root->right, prev);
    }
};


/*
Iterative solution
*/
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        TreeNode *prev = nullptr;
        stack<TreeNode *>stk;
        while(root || stk.size()){
            if(root){
                if(prev!=nullptr && root->val<=prev->val) return false;
                stk.push(root);
                root = root->left;
            }else{
                root = stk.top(); stk.pop();
                if(prev!=nullptr && root->val<=prev->val) return false;
                prev = root;
                root = root->right;
            }
        }
        return true;
    }
};



class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if(root==NULL)
            return true;
        TreeNode* pLast=NULL;
        stack<TreeNode*> stk;
        while(root!=NULL || !stk.empty())
        {
            while(root!=NULL)
            {
                stk.push(root);
                root=root->left;
            }
            root=stk.top();
            stk.pop();
            if(pLast==NULL)
                pLast=root;
            else if(pLast->val>=root->val)
                return false;
            pLast=root;
            root=root->right;
        }
        return true;
    }
};