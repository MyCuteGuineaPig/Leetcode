/*
99. Recover Binary Search Tree

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

Example 1:

Input: [1,3,null,null,2]

   1
  /
 3
  \
   2

Output: [3,1,null,null,2]

   3
  /
 1
  \
   2
Example 2:

Input: [3,1,4,null,null,2]

  3
 / \
1   4
   /
  2

Output: [2,1,4,null,null,3]

  2
 / \
1   4
   /
  3
Follow up:

A solution using O(n) space is pretty straight forward.
Could you devise a constant space solution?


*/


/*

Inorder traversal，调换node 之间第一个最错误的（也是最大的），和最后一个错误（也是最小的）

比如

   1
  /
 3
  \
   2
发现 3, 2 顺序不对，最大的是3, 最小的是2
之后发现1，2 顺序不对，keep之前最大的3，最小的是1

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
    void recoverTree(TreeNode* root) {
        TreeNode *cur, *pre;
        cur = root; pre = NULL;
        pair<TreeNode*, TreeNode*> broken;
        while(cur){
            if(!cur->left){
                detect(cur,pre,broken);
                pre = cur;
                cur = cur->right;
            }else{
                TreeNode* node = cur->left;
                while(node->right && node->right!=cur)
                    node = node->right;
                if(!node->right){
                    node->right = cur;
                    cur = cur->left;
                }else{
                    detect(cur, pre, broken);
                    node->right = NULL;
                    pre = cur;
                    cur = cur->right;
                }
                
            }
            
        }
        swap(broken.first->val, broken.second->val);
    }
    
    void detect(TreeNode *cur, TreeNode* pre, pair<TreeNode*, TreeNode*>& broken){
        if(pre && pre->val > cur->val){
            //cout<<" prev "<<pre->val<<" cur "<<cur->val<<endl;
            if(!broken.first) broken.first = pre;
            broken.second = cur;
        }
    }
};



class Solution {
public:
    void recoverTree(TreeNode* root) {
        TreeNode *cur = root, *pre = NULL, *first = NULL, *second = NULL;
        traversal(cur,pre, first, second);
        swap(first->val, second->val);
    }
    
    
    void traversal(TreeNode* cur, TreeNode*& pre, TreeNode*& first, TreeNode*& second){ //注意需要用pointer的reference
        if(!cur) return;
        if(cur->left) traversal(cur->left,pre,first,second);
        
        if(pre && pre->val > cur->val){
            if(!first) first = pre;
            second = cur;
        }
        pre = cur;
        if(cur->right) traversal(cur->right, pre, first, second);
        
    }
};