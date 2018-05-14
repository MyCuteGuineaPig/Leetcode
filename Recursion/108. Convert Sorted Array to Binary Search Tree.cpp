/*
108. Convert Sorted Array to Binary Search Tree

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of every node never differ by more than 1.

Example:

Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5

*/

/*
注意height要balance的
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums,0,nums.size()-1);
    }
    
    TreeNode *helper(vector<int>& nums, int l, int r){
        if(l>r) return nullptr;
        int mid = (l+r)>>1;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = helper(nums,l,mid-1);
        root->right = helper(nums,mid+1,r);
        return root;
    }
};



class Solution {
private:
    void toBST(vector<int>& nums, int a, int b, TreeNode* root) {
        int mid = (a + b) >> 1;
        root->val = nums[mid];
        if (mid - 1 >= a) {
            root->left = new TreeNode(0);
            toBST(nums, a, mid - 1, root->left);
        }
        if (mid + 1 <= b) {
            root->right = new TreeNode(0);
            toBST(nums, mid + 1, b, root->right);
        }
    }
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if (!nums.size()) return NULL;
        TreeNode* root = new TreeNode(0);
        toBST(nums, 0, nums.size() - 1, root);
        return root;
    }
};


/*
Iterative
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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        if(nums.empty()) return nullptr;
        queue<myQueue>q;
        int l = 0, r = nums.size()-1, mid = (l+r)>>1, newmid;
        TreeNode *node = new TreeNode(nums[mid]);
        TreeNode** curr = &node;
        q.push(myQueue(node,l,r));
        while(q.size()){
            int qsize = q.size();
            for(int i = 0; i<qsize; i++){
                myQueue top = q.front();
                curr = &top.node;
                q.pop();
                int mid = (top.left + top.right)>>1;
                if(mid>top.left){
                    newmid = (top.left + mid-1)>>1;
                    TreeNode *temp = new TreeNode(nums[newmid]);
                    (*curr)->left = temp;
                    q.push(myQueue(temp,top.left,mid-1));
                    
                }
                if(mid<top.right){
                    newmid = (mid+1 + top.right)>>1;
                    TreeNode *temp2 = new TreeNode(nums[newmid]);
                    (*curr)->right = temp2;
                    q.push(myQueue(temp2,mid+1,top.right));
                }
                
            }
        }
        return node;
    }
    
    
    class myQueue{
    public:
        TreeNode* node;
        int left;
        int right;
        myQueue(TreeNode* node, int left, int right){
            this->node = node;
            this->left = left;
            this->right = right;
        }
    };
};