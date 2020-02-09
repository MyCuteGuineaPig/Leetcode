/*
654. Maximum Binary Tree

Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
Construct the maximum tree by the given array and output the root node of this tree.

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
Note:
The size of the given array will be in the range [1,1000].

*/

/*
descending stack, 
如果现在数 num[i] 小于stack 的top，就在stack的top right child append nums[i]
比如 [3,2,1]  3
              \ 
               2
                \
                 1

如果现在数num[i] 大于stack 的top，就不断pop stack 找最后一个小于nums[i]的数，把最后的node 作为nums[i]的left child 
比如 nums[i] = 6, nums = [8,3,2,1,6]  8                         8 
                                       \                         \                          
                                        3                         6
                                         \         =》           /
                                          2                     3
                                           \                     \
                                            1                     2
                                                                   \
                                                                    1


*/

class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode*>stk;
        for(auto v: nums){
            TreeNode* cur = new TreeNode(v);
            while(!stk.empty() && stk.back()->val < v)
                cur->left = stk.back(), stk.pop_back();
            if(!stk.empty())
                stk.back()->right = cur;
            stk.push_back(cur);
        }
        return stk.front();
    }
};


class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode *> nodeStack;
        for (int i = 0; i < nums.size(); ++i) {
            auto node = new TreeNode(nums[i]);
            while (!nodeStack.empty() && nums[i] > nodeStack.back()->val) {
                node->left = nodeStack.back();
                nodeStack.pop_back();
            }
            if (!nodeStack.empty()) {
                nodeStack.back()->right = node;
            }
            nodeStack.emplace_back(node);
        }
        return nodeStack.front();
    }
};


//recusion
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return build(nums, 0, nums.size() - 1);
    }
    
    TreeNode*  build(const vector<int>& nums, int start, int end) {
        if (start > end) return nullptr;
        
        int idxMax = start;
        for (int i = start + 1; i <= end; i++) {
            if (nums[i] > nums[idxMax]) {
                idxMax = i;
            }
        }
        
        TreeNode* root = new TreeNode(nums[idxMax]);
        
        root->left = build(nums, start, idxMax - 1);
        root->right = build(nums, idxMax + 1, end);
        
        return root;
    }
};


class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        return makeMBT(nums);
    }
    
private:
    TreeNode* makeMBT(const vector<int>& vec) {
        if (vec.empty()) return nullptr;
        auto it = max_element(vec.begin(), vec.end());
        TreeNode* root = new TreeNode(*it);
        vector<int> left(vec.begin(), it);
        vector<int> right(it+1, vec.end());
        root->left = makeMBT(left);
        root->right = makeMBT(right);
        return root;
    }
};

class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode*> s { new TreeNode(nums[0]) };
        for (int i = 1; i < nums.size(); ++i) {
            TreeNode* cur = new TreeNode(nums[i]);
            auto it = upper_bound(s.rbegin(), s.rend(), cur, 
                                [](const TreeNode* a, const TreeNode* b) { return a->val < b->val; });//找第一个大于cur->val的
            if (it != s.rend()) (*it)->right = cur;
            if (it != s.rbegin()) cur->left = *next(it, -1);
            s.resize(distance(it, s.rend()));
            s.push_back(cur);
        }
        return s.front();
    }
};
