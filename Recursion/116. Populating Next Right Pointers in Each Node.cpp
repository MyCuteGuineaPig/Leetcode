/*
116. Populating Next Right Pointers in Each Node

Given a binary tree

struct TreeLinkNode {
  TreeLinkNode *left;
  TreeLinkNode *right;
  TreeLinkNode *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.

Note:

You may only use constant extra space.
Recursive approach is fine, implicit stack space does not count as extra space for this problem.
You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
Example:

Given the following perfect binary tree,

     1
   /  \
  2    3
 / \  / \
4  5  6  7
After calling your function, the tree should look like:

     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \  / \
4->5->6->7 -> NULL


*/

/*
检查有没有left，先把root left 和root right连了，如果root 有next，把root right和next left 连了，然后横着走

比如现在cur=2,  把cur->left ->next = cur->right 就是把4和5连上,
 然后看现在cur有没有cur->next，如果有，把现在cur->right->next 和cur->next->left 连上，
 然后再横向走 cur 从2到3

     1     ===》     1       ===》    1          
   /  \            /  \1           /   \
  2 -> 3          2 -> 3          2  ->  3
 / \  / \        / \ / \         / \    / \
4  5  6  7      4->5 6  7       4 ->5-> 6  7



*/
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        TreeLinkNode *cur = root;
        TreeLinkNode *pre = root;
        while(cur->left){
            pre = cur;
            while(cur){
                cur->left->next = cur->right;
                if(cur->next) cur->right->next = cur->next->left;
                cur = cur->next;
            }
            cur = pre->left;
        }
    }
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        while(root->left){
            TreeLinkNode *pre = root;
            while(root){
                root->left->next = root->right;
                if(root->next) root->right->next = root->next->left;
                root = root->next;
            }
            root = pre->left;
        }
    }
};


/*
或者是阶梯式向下connect root1 left和 root1 right & root1 right和root2 left & root2 left和root2 right
*/
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(root)
            connectTwo(root->left, root->right);
    }
    
    void connectTwo(TreeLinkNode *root1,TreeLinkNode *root2){
        if(!root1) return;
        root1->next = root2;
        if(root1->left){
            connectTwo(root1->left, root1->right);
            connectTwo(root2->left, root2->right);
            connectTwo(root1->right, root2->left);
        }
    }
};


class Solution {
public:
    void connect(TreeLinkNode *root) {
        
        connect(root, NULL);
    }
    void connect(TreeLinkNode *root, TreeLinkNode* next) {
        if(root == NULL)
            return;
        root->next = next;
        
        if(root->left == NULL)
            return;
        
        connect(root->left, root->right);        
        if(next == NULL)
            connect(root->right, NULL);
        else
            connect(root->right, next->left);
    }
};


class Solution {
public:
    void connect(TreeLinkNode *root) {
        if (!root) return;
        if (root -> left) {
            root -> left -> next = root -> right;
            if (root -> next)
                root -> right -> next = root -> next -> left;
        }
        connect(root -> left);
        connect(root -> right);
    }
};