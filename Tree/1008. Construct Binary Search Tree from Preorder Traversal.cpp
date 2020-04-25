class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if(preorder.empty())
            return nullptr;
        vector<TreeNode*>stk;
        TreeNode *res = new TreeNode(preorder[0]); 
        stk.push_back(res);
        for(int i = 1; i<preorder.size(); ++i){
            TreeNode* tree = new TreeNode(preorder[i]);
            if(preorder[i] > stk.back()->val){
                TreeNode* cur;
                while(stk.size() && preorder[i] > stk.back()->val){
                    cur = stk.back();
                    stk.pop_back();
                }
                cur->right = tree;
            }
            else
                stk.back()->left = tree;
            stk.push_back(tree);
        }
        return res;
    }
};

class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if(preorder.empty())
            return nullptr;
        TreeNode* res = new TreeNode(preorder[0]);
        stack<TreeNode*>stk; stk.push(res);
        for(int i = 1; i < preorder.size(); ++i){
            TreeNode* cur = new TreeNode(preorder[i]);
            if(cur->val < stk.top()->val )
                stk.top()->left = cur;
            else{
                TreeNode* last;
                while (!stk.empty() && stk.top()->val < cur->val){
                    last = stk.top(); 
                    stk.pop();
                }
                last->right = cur;
            }
            stk.push(cur);
        }
        return res;
    }
};


class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if(preorder.empty())
            return nullptr;
        int i = 0;
        return helper(preorder, i, numeric_limits<int>::max());
    }

    TreeNode* helper(const vector<int>&preorder, int& index, int parent){   
        if(index == preorder.size())                                                    //   8 
            return nullptr;                                                            //   /
        TreeNode *cur = new TreeNode(preorder[index++]);                              //    5      1 < 5 left
        if (index < preorder.size() && preorder[index] < cur->val) //小于现在的值      //   /   \    7 < 8 right 
            cur->left = helper(preorder, index, cur->val);                          //   1     7
        if (index < preorder.size() && preorder[index] < parent) //小于parent 
            cur->right = helper(preorder, index, parent);
        return cur;
    }
};



class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if(preorder.empty())
            return nullptr;
        int i = 0;
        return helper(preorder, i, numeric_limits<int>::max());
    }

    TreeNode* helper(const vector<int>&preorder, int& index, int parent){
        if(index == preorder.size() || preorder[index] > parent)
            return nullptr;
        TreeNode *cur = new TreeNode(preorder[index++]);
        cur->left = helper(preorder, index, cur->val);
        cur->right = helper(preorder, index, parent);
        return cur;
    }
};


//Morris Traversal
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        if(preorder.empty())
            return nullptr;
        TreeNode* root = new TreeNode(preorder[0]); 
        TreeNode *node = root;
        for(int i = 1; i<preorder.size(); ++i)
        {
            TreeNode* cur = new TreeNode(preorder[i]);
            if(node->val > preorder[i]){
                cur->right = node;
                node = node->left = cur;
            }
            else{
                while(node->right && node->right->val < preorder[i]){
                    auto tmp = node->right;
                    node->right= nullptr;
                    node= tmp;
                }
                cur->right = node->right;
                node = node->right = cur;
            }
        }    
            
        
        while(node->right)
        {
            auto tmp = node->right;
            node->right = nullptr;
            node = tmp;
        }
        /*   8 
        #   /  
        #   5 
        # /     \ 
        # 1        8 
        #   \ 
        #    5    current = 1, recursive remove 1 from 5, remove 8 from 5
        */
        return root;
    }
};