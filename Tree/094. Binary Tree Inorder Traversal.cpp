/*

94. Binary Tree Inorder Traversal


Given a binary tree, return the inorder traversal of its nodes' values.

Example:

Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]
Follow up: Recursive solution is trivial, could you do it iteratively?

*/


/*

Morris Traversal

如果没有左侧的child，代表现在最大，print value
如果有左侧child， 把现在node 连上最接近的node，左侧node的最右侧，left node的right most point

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
    vector<int> inorderTraversal(TreeNode* root) {
        TreeNode *pre, *cur;
        if(!root) return {};
        cur = root;
        vector<int>res;
        while(cur){
            if(!cur->left){
                res.push_back(cur->val);
                cur = cur->right;
            }else{
                pre = cur->left;
                while(pre->right && pre->right!=cur)
                    pre = pre->right;
                if(pre->right){
                    pre->right = NULL;
                    res.push_back(cur->val);
                    cur = cur->right;
                }
                else{
                    pre->right = cur;//第一次pass的parent node 先不操作它
                    cur = cur->left;
                }
            }
        }
        return res;
    }
};

/**
Morris Traversal 不可以用下面判断的原因

                pre = cur->left;
                if(pre->right==cur){
                     pre->right = NULL;
                    res.push_back(cur->val);
                    cur = cur->right;
                }
                else{
                    while(pre->right)
                        pre = pre->right;
                    pre->right = cur;//第一次pass的parent node 先不操作它
                    cur = cur->left;
                }

[] means has structure below, & 表示cur 
比如       --->    at point 1:    -－》   at point 2    －－>      at point 4:   -->
       1             & 1                      [1]                   4 no left, cur = 4->right = 2   
      /  \           /  \                    /  \                          [1]
     2   3           2    3               $ 2                              /
    / \ / \         /  \  /  \             / \                            2
   4  5 6  7        4   5 6   7           4    5                        /  \
                         \                  \   \                     & 4   5
                           1                  2  [1]                      \  \
                           / \              /  \                           2  [1]
                         [2]   [3]        [4]   5                         / \
                                                 \                       [4]  5
                                                  [1]                           \
                                                                                 [1]
                                                                                 
  -->  at point 2:,                       -->        at point 5:                  --->    at point  1
  pre = 2->left = 4,                                 no left, cur = 5->right              pre = cur->left = 2
  4->right == 2, pre->right = NULL                      [1]                               pre = pre -> right = 5; pre-> right == 1,  
  cur = cur->right                                       /                                pre -> right = NULL, cur = cur->right
            [1]                                         2                                        1
           /                                           /  \                                     /  \ 
          2                                           4   $ 5                                   2   [3]
         /  \                                               \                                  /  \ 
         4    5                                               1                               4    5
          x     \                                            /  \                                   x
          $ 2    [1]                                       [2]   [3]                                & 1
           / \                                                                                       / \
          4    5                                                                                   [2] [3]
           x    \
            [2]  [1]
               
               
 --> at point 3:                       -->  at point 6:
           1
          / \ 
         [2] 3
             /  \
             6  7
             \
              3
             /  \
           [6]   7
            
             
             
             
*/



//Stack
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        TreeNode *cur = root;
        if(!root) return {};
        vector<int>res;
        stack<TreeNode *>stk;
        while(cur || !stk.empty()){ //cur 比如只有右面的，stack只存之后需要返回的 ； !stk.empty() 是看是不是有接下来返回的node，比如到最左侧node 需要返回
            if(cur){
                stk.push(cur);
                cur = cur->left;
            }else{//切换到之前的top
                cur = stk.top(); stk.pop();
                res.push_back(cur->val);
                cur = cur->right;
            }
        }
        return res;
    }
};





class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        stack<TreeNode*> s;
        pushAllLeft(s, root);
        vector<int> result;
        while(!s.empty()) {
            TreeNode* p = s.top();
            s.pop();
            result.push_back(p->val);
            pushAllLeft(s,p->right);
        }
        return result;
    }
    
    void pushAllLeft(stack<TreeNode*>& s, TreeNode* root) {
        while(root) {
            s.push(root);
            root = root->left;
        }
    }
};


class Solution2 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<pair<TreeNode *, bool>> s;
        s.emplace(root, false);
        while (!s.empty()) {
            bool visited;
            tie(root, visited) = s.top();
            s.pop();
            if (root == nullptr) {
                continue;
            }
            if (visited) {
                res.emplace_back(root->val);
            } else {
                s.emplace(root->right, false);
                s.emplace(root, true);
                s.emplace(root->left, false);
            }
        }
        return res;
    }
};
