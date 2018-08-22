/*
662. Maximum Width of Binary Tree


Given a binary tree, write a function to get the maximum width of the given tree. The width of a tree is the maximum width among all levels. The binary tree has the same structure as a full binary tree, but some nodes are null.

The width of one level is defined as the length between the end-nodes (the leftmost and right most non-null nodes in the level, where the null nodes between the end-nodes are also counted into the length calculation.

Example 1:
Input: 

           1
         /   \
        3     2
       / \     \  
      5   3     9 

Output: 4
Explanation: The maximum width existing in the third level with the length 4 (5,3,null,9).
Example 2:
Input: 

          1
         /  
        3    
       / \       
      5   3     

Output: 2
Explanation: The maximum width existing in the third level with the length 2 (5,3).
Example 3:
Input: 

          1
         / \
        3   2 
       /        
      5      

Output: 2
Explanation: The maximum width existing in the second level with the length 2 (3,2).
Example 4:
Input: 

          1
         / \
        3   2
       /     \  
      5       9 
     /         \
    6           7
Output: 8
Explanation:The maximum width existing in the fourth level with the length 8 (6,null,null,null,null,null,null,7).


Note: Answer will in the range of 32-bit signed integer.



*/


/*
给每个node 一个id

比如：  
                 1
           /         \
          1           2
        /  \        /    \    
      1     2      3      4 
     / \   /  \   /  \   /  \
    1   2  3   4  5   6 7   8

    从parent ->left child = 2*id -1 
    从parent ->right child = 2*id

*/
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root, int level = 1) {
        if(!root) return 0;
        vector<pair<int,int>>bound;
        helper(root, bound, 1, 1);
        int res = 1;
        for(auto p: bound) {
            res = max(p.second - p.first+1, res);
        }
        return res;
    }
    
    void helper(TreeNode* root, vector<pair<int,int>>& bound, int id, int level){
        if(!root) return;
        if(bound.size() < level) bound.push_back({id,id});
        bound[level-1].first = min(bound[level-1].first, id);
        bound[level-1].second = max(bound[level-1].second, id);
        helper(root->left, bound,2*id-1, level+1);
        helper(root->right, bound,2*id, level+1);
    }
};


/*
        1
   2         3
 4   5     6   7
8 9 x 11  x 13 x 15


*/

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        vector<int> leftmosts;
        return dfs(root, 1, 0, &leftmosts);
    }

private:
    int dfs(TreeNode* node, int id, int depth, vector<int> *leftmosts) {
        if (!node) {
            return 0;
        }
        if (depth >= leftmosts->size()) {
            leftmosts->emplace_back(id);
        }
        int result = id - (*leftmosts)[depth] + 1;
        result = max(result, dfs(node->left, id * 2, depth + 1, leftmosts));
        result = max(result, dfs(node->right, id * 2 + 1, depth + 1, leftmosts));
        return result;
    }
};

class Solution {
public:
   int widthOfBinaryTree(TreeNode* root) {
        return dfs(root, 0, 1, vector<pair<int, int>>() = {});
    }
    
    int dfs(TreeNode* root, int level, int order, vector<pair<int, int>>& vec){
        if(root == NULL)return 0;
        if(vec.size() == level)vec.push_back({order, order});
        else vec[level].second = order;
        return max({vec[level].second - vec[level].first + 1, dfs(root->left, level + 1, 2*order, vec), dfs(root->right, level + 1, 2*order + 1, vec)});
    }
};


//BFS
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int max = 0;
        queue<pair<TreeNode*, int>> q;
        q.push(pair<TreeNode*, int>(root, 1));
        while (!q.empty()) {
            int l = q.front().second, r = l; // right started same as left
            for (int i = 0, n = q.size(); i < n; i++) {
                TreeNode* node = q.front().first;
                r = q.front().second;
                q.pop();
                if (node->left) q.push(pair<TreeNode*, int>(node->left, r * 2));
                if (node->right) q.push(pair<TreeNode*, int>(node->right, r * 2 + 1));
            }
            max = std::max(max, r + 1 - l);
        }
        return max;
    }
};


/*

When traversing the current level, 
1. try to construct the next level. When constructing, we add all nodes from next level no matter it is a null node or not.

2. Then will make the next level valid. That is, get rid of the null nodes that appear before the first non-null node and after the last non-null node.
找到左面第一个 和右面最后一个不是null的
For example:
next level when constructing: [null, 1, 2, 3, null, null, null, 4, null, null]
After validating: [1, 2, 3, null, null, null, 4]

3. Then, after validating, it is a potential width of the tree. Compare it with the existing width.

4. Do this for all levels.

*/

class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int res =1;
        deque<TreeNode*> q;
        q.push_back(root);
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = q.front(); q.pop_front();
                if(!node){
                    q.push_back(NULL); q.push_back(NULL);
                }else{
                    q.push_back(node->left);q.push_back(node->right);
                }
            }
            makeValid(q);
            res = max(res, (int)q.size());
        }
        return res;
    }
    
    void makeValid(deque<TreeNode*>& q){
        while(!q.empty() && !q.front())
            q.pop_front();
        while(!q.empty() && !q.back())
            q.pop_back();      
    }
};