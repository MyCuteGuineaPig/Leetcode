/*
95. Unique Binary Search Trees II

Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

Example:

Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3


*/


/*
Generate vector of left subtree 和right subtree, 然后排列组合把他们弄在一起
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
    vector<TreeNode*> generateTrees(int n) {
        if (n==0) return {};
        return generateSubTree(1,n);
    }
    
    vector<TreeNode *> generateSubTree(int start, int end){
        if(start>end) return {nullptr};
        else if(start == end) return {new TreeNode(start)};
        else{
            vector<TreeNode *>res;
            for(int i = start; i<=end; i++){
                vector<TreeNode *>l = generateSubTree(start, i-1);
                vector<TreeNode *>r = generateSubTree(i+1, end);
                for(int j = 0; j<l.size();j++){
                    for(int k = 0; k<r.size(); k++){
                        TreeNode *tree = new TreeNode(i);
                        tree->left = l[j];
                        tree->right = r[k];
                        res.push_back(tree);
                    }
                }
            }
            return res;
        }
    }
};


/*
recursion with memoization
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
    unordered_map<int, unordered_map<int,vector<TreeNode*>>>dp;
    vector<TreeNode*> generateTrees(int n) {
        if (n==0) return {};
        return generateSubTree(1,n);
    }
    
    vector<TreeNode *> generateSubTree(int start, int end){
        if(dp.count(start) && dp[start].count(end)) return dp[start][end];
        vector<TreeNode *>res;
        if(start>end) res.push_back(nullptr);
        else if(start == end) res.push_back(new TreeNode(start));
        else{
            for(int i = start; i<=end; i++){
                vector<TreeNode *>l = generateSubTree(start, i-1);
                vector<TreeNode *>r = generateSubTree(i+1, end);
                for(int j = 0; j<l.size();j++){
                    for(int k = 0; k<r.size(); k++){
                        TreeNode *tree = new TreeNode(i);
                        tree->left = l[j];
                        tree->right = r[k];
                        res.push_back(tree);
                    }
                }
            }
        }
        return dp[start][end] = res;
    }
};



/*
The basic idea is that we can construct the result of n node tree just from the result of n-1 node tree.
Here's how we do it: only 2 conditions: 1) The nth node is the new root, so newroot->left = oldroot;
2) the nth node is not root, we traverse the old tree, every time the node in the old tree has a right child, we can perform: 
old node->right = nth node, nth node ->left = right child; and when we reach the end of the tree, don't forget we can also add the nth node here.
One thing to notice is that every time we push a TreeNode in our result, 
I push the clone version of the root, and I recover what I do to the old node immediately. This is because you may use the old tree for several times.


之前在vector里面的都比i小
比如现在tree是     加上3可以直接加上3，因为之前2作为root，righttree是nullptr,     
            2                                                           3
           /                                                          /
          1                                                          2  
                                                                    /        
                                                                   1      



比如现在tree是     加上3可以直接加上3， 首先可以把原来的tree放在左侧，    
            1                                               3
              \                                            /
               2                                          1 
                                                           \
                                                            2
因为right tree不是nullptr, 所以要loop 之前的tree，loop right tree，每到一点就把之后的tree，作为这点的left-tree, 这的点值设为新的i
比如到达2了                   到达底部了
            1                   1
              \                   \
                3                  2
               /                    \
              2                      3

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
        TreeNode* clone(TreeNode* root){
            if(root == nullptr)
                return nullptr;
            TreeNode* newroot = new TreeNode(root->val);
            newroot->left = clone(root->left);
            newroot->right = clone(root->right);
            return newroot;
        }
        vector<TreeNode *> generateTrees(int n) {
            vector<TreeNode *> res(1,nullptr);
            for(int i = 1; i <= n; i++){
                vector<TreeNode *> tmp;
                for(int j = 0; j<res.size();j++){
                    TreeNode* oldroot = res[j];
                    if(oldroot==nullptr)
                        cout<<" i "<<i<<" j "<<j<<"  nullptr "<<endl;
                    else 
                        cout<<" i "<<i<<" j "<<j<<"  val "<<oldroot->val<<endl;
                    TreeNode* root = new TreeNode(i);
                    TreeNode* target = clone(oldroot);
                    root->left = target;
                    tmp.push_back(root);
                   
                    if(oldroot!=nullptr){
                        TreeNode* tmpold = oldroot;
                        cout<<" inf i "<<i<<" j "<<j<<"  val "<<oldroot->val<<endl;
                        while(tmpold->right!=nullptr){
                            TreeNode* nonroot = new TreeNode(i);
                            TreeNode *tright = tmpold->right;
                            tmpold->right = nonroot;
                            nonroot->left = tright;
                            TreeNode *target = clone(oldroot);
                            tmp.push_back(target);
                            tmpold->right = tright;
                            tmpold = tmpold->right;
                        }
                        tmpold->right = new TreeNode(i);
                        TreeNode *target = clone(oldroot);
                        tmp.push_back(target);
                        tmpold->right = nullptr;
                    }
                }
                res=tmp;
            }
            return res;
        }
    };
