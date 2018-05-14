/*
106. Construct Binary Tree from Inorder and Postorder Traversal

Given inorder and postorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7

*/


/*
The the basic idea is to take the last element in postorder array as the root,
 find the position of the root in the inorder array; then locate the range for left sub-tree and 
 right sub-tree and do recursion. Use a HashMap to record the index of root in the inorder array.


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
    unordered_map<int,int>inIndex;
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for(int i = 0; i<inorder.size();i++){
            inIndex[inorder[i]] = i;
        }
        return helper(postorder, postorder.size()-1, 0,postorder.size()-1);
    }
    
    TreeNode *helper(vector<int>& postorder, int pPost, int istart, int iend){
        if(istart>iend || pPost<0) return nullptr;
        int val = postorder[pPost];
        TreeNode *root = new TreeNode(val);
        root->right = helper(postorder, pPost-1,inIndex[val]+1, iend);
        root->left = helper(postorder, pPost-(iend-inIndex[val])-1, istart, inIndex[val]-1);
        return root;
    }
};


class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int p = postorder.size()-1, i = inorder.size()-1;
        return helper(postorder, inorder, p, i, -1);
    }
    
    TreeNode *helper(vector<int>& postorder,vector<int>& inorder, int &p, int &i, int prev){
        if(p<0 || (prev!=-1 && postorder[prev] == inorder[i])) return nullptr;
        TreeNode *root = new TreeNode(postorder[p--]);
        root->right = helper(postorder, inorder, p, i, p+1);
        i--;
        root->left = helper(postorder,inorder, p,i,prev);
        return root;
    }
};



/*
This is my iterative solution, think about "Constructing Binary Tree from inorder and preorder array", 
the idea is quite similar. Instead of scanning the preorder array from beginning to end and using inorder array as a kind of mark, 
in this question, the key point is to scanning the postorder array from end to beginning and also use inorder array from end to beginning as a mark 
because the logic is more clear in this way. 
The core idea is: Starting from the last element of the postorder and inorder array,
 we put elements from postorder array to a stack and each one is the right child of the last one until an element in postorder array is equal to the element on the inorder array. 
 Then, we pop as many as elements we can from the stack and decrease the mark in inorder array until the peek() element is not equal to the mark value or the stack is empty. 
 Then, the new element that we are gonna scan from postorder array is the left child of the last element we have popped out from the stack.

*/

class Solution {
 public:
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    assert(inorder.size() == postorder.size());
    if (inorder.size() == 0) return nullptr;

    TreeNode* root;
    TreeNode** curr = &root;
    auto j = postorder.crbegin();
    stack<TreeNode*> s;
    for (auto i=inorder.crbegin(); i!=inorder.crend(); ++i) {
      while (s.empty() || s.top()->val != *i) { //一直loop 到没有right tree了，
        auto node = new TreeNode{*j++};
        s.push(node);
        *curr = node;
        curr = &node->right;
      }
      /*
      inorder = [9,3,15,20,7]
      postorder = [9,15,7,20,3]
          3
         / \
        9  20
          /  \
         15   7
      比如上面的tree, 第一次直接while 7， curr = 7-left, 把7 再pop掉，剩下的top是20
      */
      curr = &(s.top()->left);//然后cur = top->left, 
      s.pop();
    }

    assert(j == postorder.crend());
    return root;
  }
};