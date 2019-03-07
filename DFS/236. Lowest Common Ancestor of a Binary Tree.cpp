/*
236. Lowest Common Ancestor of a Binary Tree

Time	Space	Difficulty
O(n)	O(h)	Medium

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes v and w as the lowest node in T that has both v and w as descendants (where we allow a node to be a descendant of itself).”

        _______3______
       /              \
    ___5__          ___1__
   /      \        /      \
   6      _2       0       8
         /  \
         7   4
For example, the lowest common ancestor (LCA) of nodes 5 and 1 is 3. Another example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
*/

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root == p || root == q) return root;
        TreeNode *left = lowestCommonAncestor(root->left, p ,q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        return left ? (right ? root : left) : right; 
    }
};


//iterative
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        //iterative, path comparing
        if(!root || root==p || root==q) return root;
        vector<TreeNode*> pathp, pathq, temp;
        temp.push_back(root); //temp是stack，元素是从root到现在node上的路径
        TreeNode* prev=NULL; //prev是用来返回到原来位置用的
        while(pathp.empty() || pathq.empty()){
            root=temp.back();
            if(root==p) pathp=temp;
            if(root==q) pathq=temp;
            if(!root->left && !root->right || !root->right && prev==root->left || root->right && prev==root->right){
                temp.pop_back();
                prev=root;
            }
            else{
                if(!root->left || prev==root->left) temp.push_back(root->right);
                else temp.push_back(root->left);
            }
        }
        int n=min(pathp.size(),pathq.size());
         for(int i=1; i<n; i++){
            if(pathp[i]!=pathq[i]) return pathp[i-1];
        }
        return pathp[n-1];
    }
};
