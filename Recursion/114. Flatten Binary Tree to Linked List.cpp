/*
114. Flatten Binary Tree to Linked List

Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:

    1
   / \
  2   5
 / \   \
3   4   6
The flattened tree should look like:

1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6

*/

/*
相当于preorder traversal的倒叙，线去root->right, 再去root->left, 再返回root，
比如1点，right 返回pre = 5-6, 再去1的左面 -> 2的右面 -> 4没有的left,right tree,直接append prev到4的右侧
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
    void flatten(TreeNode* root) {
        helper(root,nullptr);
    }
    
    TreeNode *helper(TreeNode *root, TreeNode *prev){
        if(!root) return prev;
        prev = helper(root->right,prev);
        prev = helper(root->left,prev);
        root->right = prev;
        root->left = nullptr;
        return root;
    }
};