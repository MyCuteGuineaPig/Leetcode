/*
We run a preorder depth first search on the root of a binary tree.

At each node in this traversal, we output D dashes (where D is the depth of this node), then we output the value of this node.  (If the depth of a node is D, the depth of its immediate child is D+1.  The depth of the root node is 0.)

If a node has only one child, that child is guaranteed to be the left child.

Given the output S of this traversal, recover the tree and return its root.

 

Example 1:



Input: "1-2--3--4-5--6--7"
Output: [1,2,5,3,4,6,7]
Example 2:



Input: "1-2--3---4-5--6---7"
Output: [1,2,5,3,null,6,null,4,null,7]
 

Example 3:



Input: "1-401--349---90--88"
Output: [1,401,null,349,88,90]
 

Note:

The number of nodes in the original tree is between 1 and 1000. 
Each node will have a value between 1 and 10^9.
*/

class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
        vector<TreeNode*>stk;
        int index = 0;
        while(index < S.length()){
            int level = 0, val = 0;
            while (index < S.length() && S[index]=='-') level ++, index++;
            while(index < S.length() && S[index] !='-') val = val*10 + S[index]-'0',index ++; 
            
            TreeNode* curNode = new TreeNode(val);
            while(level < stk.size()) stk.pop_back();
            if (!stk.empty() && !stk.back()->left)
                stk.back()->left = curNode;
            else if (!stk.empty())
                stk.back()->right = curNode;
            stk.push_back(curNode);
        }
        return stk[0];
    }
};



class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
        unordered_map<int, TreeNode*> tbl;
        TreeNode* res = NULL;
        
        queue<pair<int, int>> q;
        
        for (int i = 0; i < S.size(); ) {
            int c = 0;
            int n = 0;
            
            while (i < S.size() && S[i] == '-') { c++; i++; }
            
            while (i < S.size() && S[i] != '-') { n *= 10; n += (S[i] - '0'); i++; }
                        
            q.push(make_pair(c, n));
        }
        
        while (!q.empty()) {
            auto i = q.front(); q.pop();
            
            TreeNode* cur = new TreeNode(i.second);
            
            tbl[i.first] = cur;
            
            if (!i.first) res = cur;
            else {
                auto x = tbl[i.first - 1];
                
                if (x->left == NULL)
                    x->left = cur;
                else x->right = cur;
            }
        }
        
        return res;
    }
};




class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
        int i = 0;
        return dfs(S, i, 0);
    }

    TreeNode* dfs(const string& S, int& i, int depth) {
        if (i == S.length()) return nullptr;
        for (int j = 0; j < depth; j++) {
            if (S[i + j] != '-') return nullptr;
        }
        i += depth;
        int j = i;
        while (j < S.length() && isdigit(S[j])) {
            j++;
        }
        int val = stoi(S.substr(i, j - i));
        i = j;
        TreeNode* root = new TreeNode(val);
        root->left = dfs(S, i, depth + 1);
        root->right = dfs(S, i, depth + 1);
        return root;
    }
};


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
    TreeNode* buildTree(const vector<int>&levels,const vector<int>&nums, int l, int& i){
        if(i >= nums.size()) return nullptr;
        TreeNode* cur = new TreeNode(nums[i++]);
        if(i == nums.size()) return cur;
        if(levels[i-1] == l)
            cur->left = buildTree(levels, nums, l+1, i);
        if(i <= levels.size() && levels[i-1] == l)
            cur->right = buildTree(levels, nums, l+1, i);
        return cur;
    }
    
    TreeNode* recoverFromPreorder(string S) {
        if(S.size() == 0) return nullptr;
        int index = S.find('-');
        int num = stoi(S.substr(0, index));
        vector<int> nums = {num};
        vector<int>levels;
        while(index < S.size()){
            int j = index; 
            while(S[j] == '-') ++j;
            int level = j-index;  levels.push_back(level);
            index = S.find('-',j);
            
            num = stoi(S.substr(j, index - j));
            nums.push_back(num);
        }
        int i = 0;
        return buildTree(levels, nums,1, i);
    }
};
