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

/*
把右面的tree 弄到左边tree最大的node右测，然后root右面的等于左侧的。左侧等于null, root = root->right
比如：
    1             变成         1              ==》      1              =》 root从1等于2，再repeat以上的步骤
   / \                       /  \                        \
  2   5                     2   5                         2
 / \   \                   / \    \                      /  \
3   4   6                 3  4    6                     3    4
                              \                                \
                              5                                 5
                               \                                 \
                               6                                  6

*/

/*
Time is O(n), here's why:

Moving root over all nodes and for each one potentially dive down deep into its left subtree, 
so one might think it's more than O(n) time. But... a long path down the left subtree immediately pays off,
as you then insert that entire path into the "right border" of the whole tree, 
where now will walk over it once more but t will never have to walk over it again.

To put it differently: Every node is visited by Root exactly once and by t at most once, (root 和 t都最多经过每个点1次)
and the runtime is proportional to the number of steps taken by root and t, so O(n) overall.

*/

class Solution {
public:
    void flatten(TreeNode* root) {
        while(root){
            if(root->left && root ->right){
                TreeNode *t = root->left;
                while(t->right)
                    t = t->right;
                cout<<" t "<<t->val<<endl;
                t->right = root->right;
            }
            if(root->left)
                root->right = root->left; 
            //root->right = root->left; //如果不加if，结果不对，因为假如右侧有，但是左侧没有，一append，右侧的就没了
            root->left = NULL;
            root = root->right;
        }
    }
};


class Solution {
public:
    void flatten(TreeNode* node) {
        while (node) {
            if (node->left) {
                TreeNode *prev = node->left;
                while (prev->right) {
                    prev = prev->right;
                }
                prev->right = node->right;
                node->right = node->left;
                node->left = NULL;
            }
            node = node->right;
        }
    }
};

/*
把右面的tree 弄到左边tree最大的node右测，然后root右面的等于左侧的。左侧等于null, root = root->right
比如：
    1             变成         1              ==》      1              =》    1             =>   1
   / \                       /  \                     /  \                 /   \                \
  2   5                     2   5                    2    5                2    5                2
 / \   \                   /     \                    \     \               \    \                \ 
3   4   6                 3      6                     3     6               3    6                3
                           \                           \                      \                     \ 
                            4                           4                      4                     4
                                                                                \                     \
                                                                                 5                     5 
                                                                                  \                     \
                                                                                   6                    6

*/

class Solution {
public:
    void flatten(TreeNode* root) {
        if(!root) return;
        flatten(root->left);
        flatten(root->right);
        if(!root->left) return;
        TreeNode *t = root->left;
        while(t->right)
            t = t->right;
        t->right = root->right;
        root->right = root->left;
        root->left = NULL;
    }
};

//write by own
class Solution {
public:
    void flatten(TreeNode* root) {
        if(!root) return;
        flatten(root->left);
        flatten(root->right);
        TreeNode* t = root->left;
        while(t && t->right)
            t = t->right;
        if(t){ //
            t->right = root->right;
            root->right =root->left;
            root->left = nullptr;
            /*
                5
                  \ 
                   6, 
                如果5 没有left，就不用 root->right =root->left; 否则6就被抹了
            
            */
        }
        return;
    }
    
    
};
