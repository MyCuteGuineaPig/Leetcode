/*
606. Construct String from Binary Tree

You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.

The null node needs to be represented by empty parenthesis pair "()". 
And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.

Example 1:
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /    
  4     

Output: "1(2(4))(3)"

Explanation: Originallay it needs to be "1(2(4)())(3()())", 
but you need to omit all the unnecessary empty parenthesis pairs. 
And it will be "1(2(4))(3)".
Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \  
      4 

Output: "1(2()(4))(3)"

Explanation: Almost the same as the first example, 
except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the output.

*/


class Solution {
public:
    string tree2str(TreeNode* t) {
        string out;
        helper(t, out);
        return out;
    }
    
    void helper(TreeNode* root, string& out){
        if(!root) return;
        out += to_string(root->val);
        if(root->left) {
            out += "(";
            helper(root->left, out);
            out += ")";
        }else if(root->right){
            out += "()";
        }
        if(root->right){
            out += "(";
            helper(root->right, out);
            out += ")";
        }
    }
};


class Solution {
public:
    string tree2str(TreeNode* t) {
        if (!t) {
            return "";
        }

        auto s = to_string(t->val);

        if (t->left || t->right) {
            s += "(" + tree2str(t->left) + ")";
        }
        
        if (t->right) {
            s += "(" + tree2str(t->right) + ")";
        }

        return s;
    }
};


class Solution {
public:
    string tree2str(TreeNode* t) {
        return !t ? "" : to_string(t->val) + (t->left ? "(" + tree2str(t->left) + ")" : t->right ? "()" : "")
                                           + (t->right ? "(" + tree2str(t->right) + ")" : "");
    }
};