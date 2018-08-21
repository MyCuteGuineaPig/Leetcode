/*
623. Add One Row to Tree

Given the root of a binary tree, then value v and depth d, 
you need to add a row of nodes with value v at the given depth d. The root node is at depth 1.

The adding rule is: given a positive integer depth d, for each NOT null tree nodes N in depth d-1, 
create two tree nodes with value v as N's left subtree root and right subtree root. 
And N's original left subtree should be the left subtree of the new left subtree root, 
its original right subtree should be the right subtree of the new right subtree root. 
If depth d is 1 that means there is no depth d-1 at all, 
then create a tree node with value v as the new root of the whole original tree, and the original tree is the new root's left subtree.

Example 1:
Input: 
A binary tree as following:
       4
     /   \
    2     6
   / \   / 
  3   1 5   

v = 1

d = 2

Output: 
       4
      / \
     1   1
    /     \
   2       6
  / \     / 
 3   1   5   

Example 2:
Input: 
A binary tree as following:
      4
     /   
    2    
   / \   
  3   1    

v = 1

d = 3

Output: 
      4
     /   
    2
   / \    
  1   1
 /     \  
3       1
Note:
The given d is in range [1, maximum depth of the given tree + 1].
The given binary tree has at least one tree node.

*/



class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d, int l = 1, bool isLeft = true) {
        if(l == d){
            TreeNode *cur = new TreeNode(v);
            if(isLeft) cur->left = root;
            else cur->right = root;
            return cur;
        }
        
        if(!root) return root;
        else if(l<d){
            root->left = addOneRow(root->left, v, d, l+1, true);
            root->right = addOneRow(root->right, v, d, l+1, false);
        }
        return root;
    }
};

class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if (d == 0 || d == 1) { //因为正常情况 d不能为0，d为0表示child 来自parent的右侧
            auto node = new TreeNode(v);
            (d == 1 ? node->left : node->right) = root;
            return node;
        }
        if (root && d >= 2) {
            root->left  = addOneRow(root->left,  v, d > 2 ? d - 1 : 1);
            root->right = addOneRow(root->right, v, d > 2 ? d - 1 : 0);
        }
        return root;
    }
};



class Solution {
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        vector<TreeNode*> BFSvec(1,root);
        int currLevel = 1;
        
        if(d == 1){
            TreeNode* newRoot = new TreeNode(v);
            newRoot->left = root;
            root = newRoot;
            return root;
        }
        
        while(BFSvec.size()){
            vector<TreeNode*> BFStemp = BFSvec;
            BFSvec.clear();
            while(BFStemp.size()){
                TreeNode* currNode = BFStemp.back();
                BFStemp.pop_back();
                if(!currNode){
                    continue;
                }
                if(currLevel == d-1){
                    TreeNode* leftNode = currNode->left;
                    TreeNode* rightNode = currNode->right;
                    
                    currNode->left = new TreeNode(v);
                    currNode->left->left = leftNode;
                    
                    currNode->right = new TreeNode(v);
                    currNode->right->right = rightNode;
                }
                else{
                    BFSvec.push_back(currNode->right);
                    BFSvec.push_back(currNode->left);
                }
            }
            ++currLevel;
        }
        
        return root;
        
    }
};

class Solution {
public:
    void addOneRowR(TreeNode* root, int v, int d, int cd) {
        if (!root) return;
        
        if (cd == d) {
            TreeNode *savLeft = root->left;
            root->left = new TreeNode(v);
            root->left->left = savLeft;
            
            TreeNode *savRight = root->right;
            root->right = new TreeNode(v);
            root->right->right = savRight;
            return;
        }
        addOneRowR(root->left, v, d, cd + 1);
        addOneRowR(root->right, v, d, cd + 1);
    }
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        if (d == 1) {
            TreeNode *newRoot = new TreeNode(v);
            newRoot->left = root;
            return newRoot;
        }
        addOneRowR(root, v, d, 2);
        return root;
    }
};