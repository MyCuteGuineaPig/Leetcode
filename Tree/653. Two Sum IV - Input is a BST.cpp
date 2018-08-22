/*
653. Two Sum IV - Input is a BST

Given a Binary Search Tree and a target number, 
return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
Example 2:
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False

*/

class Solution {
public:
    unordered_set<int>set;
    bool findTarget(TreeNode* root, int k) {
        if(!root) return false;
        if (set.count(k - root->val)) return true;
        set.insert(root->val);
        return findTarget(root->left, k) || findTarget(root->right, k);
    }
};

//balance search tree 用two pointer，先取得所有数的值（从小到大）
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        stack<TreeNode*> stk;
        vector<int> in_order;
        TreeNode* curr = root;
        while (true) {
            goAlongLeftBranch(curr, stk);
            if (stk.empty()) break;
            curr = stk.top();
            stk.pop();
            in_order.push_back(curr->val);
            curr = curr->right;
        }
        int i = 0, j = in_order.size()-1;
        while (i < j) {
            if (in_order[i] + in_order[j] == k) return true;
            else if (in_order[i] + in_order[j] > k) --j;
            else ++i;
        }
        return false;
    }
private:
    void goAlongLeftBranch(TreeNode* curr, stack<TreeNode*>& stk) {
        while (curr != nullptr) {
            stk.push(curr);
            curr = curr->left;
        }
    }
};


/*


The idea is to use binary search method. For each node, we check if k - node.val exists in this BST.

Time Complexity: O(nh), Space Complexity: O(h). h is the height of the tree, which is logn at best case, and n at worst case.
*/

class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        return dfs(root, root,  k);
    }
    
    bool dfs(TreeNode* root,  TreeNode* cur, int k){
        if(cur == NULL)return false;
        return search(root, cur, k - cur->val) || dfs(root, cur->left, k) || dfs(root, cur->right, k);
    }
    
    bool search(TreeNode* root, TreeNode *cur, int value){
        if(root == NULL)return false;
        return (root->val == value) && (root != cur) 
            || (root->val < value) && search(root->right, cur, value) 
                || (root->val > value) && search(root->left, cur, value);
    }
};

/* 
Iterator

l的顺序是inorder, r的顺序是 inorder的reverse

*/
class BSTIterator {
    stack<TreeNode*> s;
    TreeNode* node;
    bool forward;
    int cur;
public:
    BSTIterator(TreeNode *root, bool forward) : node(root), forward(forward) { (*this)++; };
    int operator*() { return cur; }
    void operator++(int) {
        while (node || !s.empty()) {
            if (node) {
                s.push(node);
                node = forward ? node->left : node->right;
            }
            else {
                node = s.top();
                s.pop();
                cur = node->val;
                node = forward ? node->right : node->left;
                break;
            }
        }
    }
};
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;
        BSTIterator l(root, true);
        BSTIterator r(root, false);
        while (*l < *r) {
            if (*l + *r == k) return true;
            else if (*l + *r < k) l++;
            else r++;
        }
        return false;
    }
};