/*
222. Count Complete Tree Nodes

Given a complete binary tree, count the number of nodes.

Note:

Definition of a complete binary tree from Wikipedia:
In a complete binary tree every level, except possibly the last, is completely filled, 
and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

Example:

Input: 
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6


*/


/*
Explanation

The height of a tree can be found by just going left. Let a single node tree have height 0.
 Find the height h of the whole tree. If the whole tree is empty, i.e., has height -1, there are 0 nodes.

Otherwise check whether the height of the right subtree is just one less than that of the whole tree, 
meaning left and right subtree have the same height.

If yes, then the last node on the last tree row is in the right subtree and the left subtree is a full tree of height h-1. 
So we take the 2^h-1 nodes of the left subtree plus the 1 root node plus recursively the number of nodes in the right subtree.

If no, then the last node on the last tree row is in the left subtree and the right subtree is a full tree of height h-2. 
So we take the 2^(h-1)-1 nodes of the right subtree plus the 1 root node plus recursively the number of nodes in the left subtree.

Since I halve the tree in every recursive step, I have O(log(n)) steps. Finding a height costs O(log(n)). So overall O(log(n)^2).

*/


/*

 思路：
    分治思想，树的结点数=左子树的节点数+右子树的结点数+1
    完全二叉树，如果从左子结点开始沿着其左子结点一直到叶结点的深度值lh，从右子结点开始沿着左子结点一直到叶结点的深度值rh。
    如果lh==rh, 则左子树为满二叉树，二叉树的节点数=(2^lh)-1 + 右子树的结点数 + 1，即二叉树的节点数=2^lh + 右子树的结点数
    否则二叉树的节点数=(2^rh)-1 + 左子树的结点数 + 1，即二叉树的节点数=2^rh + 左子树的结点数
    

比如
Input: 
              1
         /       \
        2         3
      /  \       /  \
     4   5       6    7 
    / \  / \    / \
  11  12 13 14 15  16

    如果height(root->right) != height(root), height(root->right) 肯定等于 height(root)-2
    相当于root->right 填到倒数第二层(比如7)， 

    如果root是leave，height(root) = 0, 且没有root->right, height(root->right) = -1  ==  height(root)-1; 

    step1, 
        root->val = 1,   height = 3,  height(root->right) == h-1:
        1<<h = 8 + countNode(3) = 8 + 5 = 13
   
    step2, 
        root->val = 3,   height = 2,  height(root->right) != h-1:
        1<<(h-1) + countNode(6) = 2 + countNode(6) = 2 + 3 = 5

    step3, 
        root->val = 6,   height = 1,  height(root->right) == h-1:
        1<<h + countNode(6) = 2 + countNode(16) = 2 + 1 = 3

    step4, 
        root->val = 16,   height = 0,  height(root->right) = -1 == h-1:
        1<<h = 1 


*/




/**
 * Recursive Solution
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
    int countNodes(TreeNode* root) {
        int h = height(root);
        return h < 0 ? 0 : height(root->right) == h-1 ?  (1<<h) + countNodes(root->right) : (1<<h-1) + countNodes(root->left);
    }
    
    int height(TreeNode* root ){
        return root ? 1+height(root->left): -1;
    }
};



/**
 * Iterative Solution
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
    int countNodes(TreeNode* root) {
        int h = 0, res  = 0;
        while((h = height(root))>=0){
            if(height(root->right) == h-1)
            {
                res += 1<<h;
                root = root->right;
            }else{
                res += 1<<h-1;
                root = root->left;
            }
        }
        return res;
    }
    
    int height(TreeNode* root ){
        return root ? 1+height(root->left): -1;
    }
};


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
    int height(TreeNode* root) {
        return !root ? -1 : 1 + height(root->left);
    }
    int countNodes(TreeNode* root) {
        int h = height(root);
        int res = 0;
        if (root)
            cout<<" h "<<h<<" root "<<root->val<<endl;
        if (h<0)
            return 0;
        if ( height(root->right) == h-1){
            cout<<" root "<<root->val<<" + (1 << h) "<<(1 << h)<<endl;
            res = (1 << h) + countNodes(root->right);
            cout<<" after h-1 "<<" root "<<root->val<<" res "<<res<<endl;
        }
        else{
            cout<<" root "<<root->val<<" + (1 << h-1) "<<(1 << h-1)<<endl;
            res = (1 << h-1) + countNodes(root->left);
            cout<<" after else "<<" root "<<root->val<<" res "<<res<<endl;
        }
        
        return res;
    }
};



class Solution {

public:

    int countNodes(TreeNode* root) {

        if(!root) return 0;

        int hl=0, hr=0;

        TreeNode *l=root, *r=root;

        while(l) {hl++;l=l->left;}

        while(r) {hr++;r=r->right;}

        if(hl==hr) return pow(2,hl)-1;

        return 1+countNodes(root->left)+countNodes(root->right);

    }

};