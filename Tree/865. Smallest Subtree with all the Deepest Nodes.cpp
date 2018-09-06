/*
865. Smallest Subtree with all the Deepest Nodes


Given a binary tree rooted at root, the depth of each node is the shortest distance to the root.

A node is deepest if it has the largest depth possible among any node in the entire tree.

The subtree of a node is that node, plus the set of all descendants of that node.

Return the node with the largest depth such that it contains all the deepest nodes in its subtree.

 

Example 1:

Input: [3,5,1,6,2,0,8,null,null,7,4]
Output: [2,7,4]
Explanation:



We return the node with value 2, colored in yellow in the diagram.
The nodes colored in blue are the deepest nodes of the tree.
The input "[3, 5, 1, 6, 2, 0, 8, null, null, 7, 4]" is a serialization of the given tree.
The output "[2, 7, 4]" is a serialization of the subtree rooted at the node with value 2.
Both the input and output have TreeNode type.
 

Note:

The number of nodes in the tree will be between 1 and 500.
The values of each node are unique.


              1
         /        \ 
       2             3
     /   \          /   \
   4      5      6     7
         /    \
       8        9
     /  \      /  \
  10   11    12    13
The answer is not [8,10,11] or [9,12,13]
the answer is [5,8,9,10,11,12,13]

*/



// 看左右高度的，如果左level  = 右level,  返回level 大的一层的node, 如果两边node level一样，返回current root
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        return dfs(root).node;
    }

private:
    struct Result {
        TreeNode *node;
        int depth;
    };

    Result dfs(TreeNode *node) {
        if (!node) {
            return {nullptr, 0};
        }
        auto left = dfs(node->left);
        auto right = dfs(node->right);
        if (left.depth > right.depth) {
            return {left.node, left.depth + 1};
        }
        if (left.depth < right.depth) {
            return {right.node, right.depth + 1};
        }
        return {node, left.depth + 1};
    }
};


 
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        return deep(root).second;
    }
    pair<int,TreeNode*> deep(TreeNode* root) 
    {
        if(!root) return {0,NULL};
        pair<int, TreeNode*> l = deep(root->left);
        pair<int, TreeNode*> r = deep(root->right);
        int a = l.first, b = r.first;
        return {max(a,b)+1, a==b ? root: (a > b ? l.second:r.second)};
    }
};


//DFS 如果left == right 的height,且left == right == 最深的, res = root
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        TreeNode* res = root; int deepest = -1;
        helper(root, 0, res, deepest);
        return res;
    }

    int helper(TreeNode* root, int dis,TreeNode*& res, int& deepest){
        if(!root) return dis;
        int left = helper(root->left, dis+1, res, deepest);
        int right = helper(root->right, dis+1, res,deepest);
        deepest = max(deepest, max(left, right));
        if(left == right && left == deepest) res = root;
        return max(left, right);
    }
};


//看左右两侧的高度
class Solution {
    int helper(TreeNode* root,int level,TreeNode* &ret){
        if(!root)return level;
        level++;
        TreeNode *lt=NULL,*rt=NULL;
        int a=helper(root->left,level,lt);
        int b=helper(root->right,level,rt);
        if(a>b)
        {
            ret = lt;
            return a;
        }
        else if(a<b)
        {
            ret = rt;
        }
        else
        {
            ret = root;
        }
        return b;
    }
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        TreeNode *ret=NULL;
        helper(root,0,ret);
        return ret;
    }
};

class Solution {
public:
    int depth(TreeNode *root) {
        return !root ? 0 : max(depth(root->left), depth(root->right)) + 1;
    }

    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        int d = depth(root->left) - depth(root->right);
        return !d ? root : subtreeWithAllDeepest(d > 0 ? root->left : root->right);
    }
};


//BFS 先找到最深的左侧和右侧的root, 然后再往上推parent
class Solution {
public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        queue<TreeNode*>q;
        if(root) q.push(root);
        TreeNode* leftmost = nullptr, *rightmost = nullptr;
        while(!q.empty()){
            int size = q.size();
            for(int i = 0; i<size; i++){
                TreeNode* cur = q.front();
                q.pop();
                if(i == 0) leftmost = cur;
                if(i == size-1) rightmost = cur;
                
                if(cur->left) q.push(cur->left);
                if(cur->right) q.push(cur->right); 
            } 
        }
        return LCA(root, leftmost, rightmost);
    }   

    TreeNode* LCA(TreeNode* root, TreeNode* leftmost, TreeNode* rightmost){
        if(!root || root == leftmost || root == rightmost) return root;
        TreeNode *l = LCA(root->left, leftmost, rightmost);
        TreeNode *r = LCA(root->right, leftmost, rightmost);
        if(l && r) return root;
        return l ? l : r;
    }
};


//[3,5,1,6,2,0,8,null,null,null,4]
