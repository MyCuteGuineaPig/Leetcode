/*
173. Binary Search Tree Iterator


Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST.

Calling next() will return the next smallest number in the BST.

Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree.




*/



/*
Queue
*/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class BSTIterator {
public:
    queue<int>q;
    BSTIterator(TreeNode *root) {
        helper(root);
    }

    void helper(TreeNode* root){
        if(!root) return;    
        helper(root->left);
        q.push(root->val);
        helper(root->right);
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !q.empty();
    }

    /** @return the next smallest number */
    int next() {
        int res = q.front();
        q.pop();
        return res;
    }
};

/**
 * Your BSTIterator will be called like this:
 * BSTIterator i = BSTIterator(root);
 * while (i.hasNext()) cout << i.next();
 */





/**
Stack
 */
class BSTIterator {
public:
    TreeNode* cur;
    stack<TreeNode*>stk;
    BSTIterator(TreeNode* root) {
        cur = root;
    }
    
    /** @return the next smallest number */
    int next() {
        int val;
        while(cur || !stk.empty()){
            if(cur){
                stk.push(cur);
                cur = cur->left;
            }else{
                cur = stk.top();
                stk.pop();
                val = cur->val;
                cur = cur->right;
                break;
            }
        }
        return val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return cur || !stk.empty();
    }
};



class BSTIterator {
public:
    BSTIterator(TreeNode *root) : cur_(root) {
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !s_.empty() || cur_ != nullptr;
    }

    /** @return the next smallest number */
    int next() {
        // Go to the left most descendant.
        while (cur_ != nullptr) {
            s_.emplace(cur_);
            cur_ = cur_->left;
        }
        cur_ = s_.top();  // Left most node.
        s_.pop();

        const auto *node = cur_;
        cur_ = cur_->right;  // Visit right child.

        return node->val;
    }

private:
    stack<TreeNode *> s_;
    TreeNode *cur_;
};




class BSTIterator {
    stack<TreeNode*> pathnode;
public:
    BSTIterator(TreeNode *root) {
        TreeNode *cur=root;
        while(cur){
            pathnode.push(cur);
            cur=cur->left;//先走左面， next再走右面
        }
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !pathnode.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *cur=pathnode.top();
        pathnode.pop();
        int res=cur->val;
        cur=cur->right;
        while(cur){
            pathnode.push(cur);
            cur=cur->left;
        }
        return res;
    }
};


/*
The average time complexity of next() function is O(1) indeed in your case. 
As the next function can be called n times at most, 
and the number of right nodes in self.pushAll(tmpNode.right) function is maximal n in a tree which has n nodes, 
so the amortized time complexity is O(1).
*/

class BSTIterator {
    stack<TreeNode *> myStack;
public:
    BSTIterator(TreeNode *root) {
        pushAll(root);
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !myStack.empty();
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *tmpNode = myStack.top();
        myStack.pop();
        pushAll(tmpNode->right);
        return tmpNode->val;
    }

private:
    void pushAll(TreeNode *node) {
        for (; node != NULL; myStack.push(node), node = node->left);
    }
};
