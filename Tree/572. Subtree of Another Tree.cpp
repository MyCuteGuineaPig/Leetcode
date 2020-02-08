/*
572. Subtree of Another Tree

Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. 
A subtree of s is a tree consists of a node in s and all of this node's descendants. 
The tree s could also be considered as a subtree of itself.

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4 
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.
Example 2:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.

*/


class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(!s) return false;
        if(isSame(s,t)) return true;
        return isSubtree(s->left, t) || isSubtree(s->right, t);
    }
    
    bool isSame(TreeNode* s, TreeNode* t){
        if(!s && !t) return true;
        if (!s || !t)  return false;
        return s->val == t->val && isSame(s->left, t->left) && isSame(s->right, t->right); 
    }
};


class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        return !t || s && (same(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t));
    }

private:
    bool isSameTree(TreeNode* s, TreeNode* t) {
        return !s ? !t : t && s->val == t->val && isSameTree(s->left, t->left) && isSameTree(s->right, t->right);
    }
};


class Solution {
public:
    void inorder(TreeNode *root,string& ans){
        if(!root){
            if(ans.empty())
                ans+="null";
            else
                ans+=",null";
            return;    
        }         
        ans+="#";            
        ans+=to_string(root->val);
        inorder(root->left,ans);
        inorder(root->right,ans);
        return; 
    }

    bool isSubtree(TreeNode* s, TreeNode* t){
         string s1,t1;
         inorder(s,s1);
         inorder(t,t1);
        
         return (s1.find(t1)!= std::string::npos);
    }
     
     
     class Solution {
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(!t ) return false;
        ostringstream in1, in2;
        seralization(in1, s);
        seralization(in2, t);
        return in2.str().find(in2.str()) != string::npos;
    }

    void seralization(ostringstream& in, TreeNode* root){
        if(!root){
            in << "# ";
            return;
        }
        seralization(in, root->left);
        in << root->val << ' ';
        seralization(in, root->right);
    }
};
};
