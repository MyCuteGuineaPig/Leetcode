/*
230. Kth Smallest Element in a BST

Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.

Note: 
You may assume k is always valid, 1 ≤ k ≤ BST's total elements.

Follow up:
What if the BST is modified (insert/delete operations) often and you need to find the kth smallest frequently?
 How would you optimize the kthSmallest routine?

*/

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {		
		vector<int> nodes;
		func(nodes,root);
		return nodes[k-1];
    }
	void func(vector<int>& nodes, TreeNode* root)
	{
        if(root)
        {
            func(nodes,root->left);
		    nodes.push_back(root->val);
		    func(nodes,root->right);
        }
		
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
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode *>stk;
        TreeNode *cur = root;
        stk.push(root);
        while(stk.size()){
            if(cur){
                stk.push(cur);
                cur = cur->left;
            }else{
                cur = stk.top();
                stk.pop();
                if(--k == 0)
                    return cur->val;
                cur = cur->right;
            }
        }
        return -1;
    }
};




/*
iterative 的解
*/
class Solution {
public:
    int getMinimumDifference(TreeNode* root) {
        int prev = numeric_limits<int>::min();
        int result = numeric_limits<int>::max();
        int start = root->val;
        stack<TreeNode*>stk;stk.push(root);
        bool top = false; //这个的作用是因为top root 被push 进了两回，第一回在初始化
        //因为binary search tree 不可能有相同的element，所以一旦遇见top，让bool 为true，
        /*
            1
             \ 
               3
              /
              2     
              top（val=1) 被push 进两回，但是假如pass 全部完了 cur = stk.top(), cur是1，最后一次loop 的 prev = 2， 
              这样 1-2 = -1 变成新的最小的, 然后因为pop之后stk size = 0，不会再继续，但这是错误的,
              
              bst 每个点的值都不一样，一样hit 到top-value，就让算法，不会hit到第二回
        */

        while(stk.size()){
            if(root){
                stk.push(root); //第二回在第一次encounter top的时候
                cout<<root->val<<endl;
                root = root->left;
            }else{
                root = stk.top();
                stk.pop();
                if(prev!=numeric_limits<int>::min() && (!top || root->val!=start)){
                    result = min(result, root->val - prev);
                }
                if(root->val == start)
                    top = true;
                prev = root->val;
                root = root->right;
            }
        }
        return result;
    }
};