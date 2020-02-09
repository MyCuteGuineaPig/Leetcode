/*
655. Print Binary Tree


Print a binary tree in an m*n 2D string array following these rules:

1. The row number m should be equal to the height of the given binary tree.
2. The column number n should always be an odd number.
3. The root node's value (in string format) should be put in the exactly middle of the first row it can be put. 
    The column and the row where the root node belongs will separate the rest space into two parts 
    (left-bottom part and right-bottom part). You should print the left subtree in the left-bottom part and print the right subtree in the right-bottom part. 
    The left-bottom part and the right-bottom part should have the same size. 
    Even if one subtree is none while the other is not, 
    you don't need to print anything for the none subtree but still need to leave the space as large as that for the other subtree. 
    However, if two subtrees are none, then you don't need to leave space for both of them.

4. Each unused space should contain an empty string "".
5. Print the subtrees following the same rules.
Example 1:
Input:
     1
    /
   2
Output:
[["", "1", ""],
 ["2", "", ""]]
Example 2:
Input:
     1
    / \
   2   3
    \
     4
Output:
[["", "", "", "1", "", "", ""],
 ["", "2", "", "", "", "3", ""],
 ["", "", "4", "", "", "", ""]]
Example 3:
Input:
      1
     / \
    2   5
   / 
  3 
 / 
4 
Output:

[["",  "",  "", "",  "", "", "", "1", "",  "",  "",  "",  "", "", ""]
 ["",  "",  "", "2", "", "", "", "",  "",  "",  "",  "5", "", "", ""]
 ["",  "3", "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]
 ["4", "",  "", "",  "", "", "", "",  "",  "",  "",  "",  "", "", ""]]
Note: The height of binary tree is in the range of [1, 10].


       1
     /    \
    2        3
   / \    /    \
  4  5    6      7 
 /\  /\   / \   /  \
8 9 10 11 12 13 14 15


output:
[  ["",  "", "",   "", "",  "",   "", "1", "",  "",  "", "",  "",  "",  ""],
   ["", "",  "",  "2"," ",   "",  "", "",  "",  "", "",  "3",  "", "",  ""],
   ["", "4", "",  "",  "",  "5",  "", "", "",  "6",  "",  "",  "","7",   ""],
   ["8", "", "9", "", "10", "", "11", "", "12", "", "13", "", "14", "", "15"]]

中心是 2^3 - 1 = 7
第2行是 7 - 2^2 = 3, 7 +2^2 = 11
第三行是  3 - 2^1 = 1, 3 + 2^1 = 5
最后一行是  1 - 2^0 = 0，  1+ 2^0 = 2

*/


//最快解
class Solution {
public:
    int helper(TreeNode* root, vector<vector<vector<int>>>&tmp, int left, int h){
        if(!root) return h-1;
        if(tmp.size() == h)
            tmp.push_back({{root->val, left}});
        else
            tmp[h].push_back({root->val, left});
        int l = helper(root->left, tmp, 2*(left+1)-2, h+1);
        int r = helper(root->right, tmp, 2*(left+1)-1, h+1);
        return max(l,r);
    }
    
    vector<vector<string>> printTree(TreeNode* root) {
        vector<vector<vector<int>>>tmp;
        int h = helper(root, tmp, 0, 0);
        int width = pow(2,h+1)-1;
        vector<vector<string>>res(h+1, vector<string>(width));
        for(int i = 0; i<tmp.size(); ++i){
            for(auto v: tmp[i]){
                int left = pow(2, h-i)-1;
                int interval = pow(2, h+1-i);
                int pos = v[1];
                res[i][left + interval*pos] = to_string(v[0]);
                
            }
        }
        return res;
    }
};


class Solution {
public:
    vector<vector<string>> printTree(TreeNode* root) {
        int h = height(root);
        vector<vector<string>>res(h, vector<string>( (1<<h)-1, ""));
        fill(root,res, h, pow(2,h-1)-1);
        return res;
    }

    int height(TreeNode* root){
        return !root ? 0 : 1 + max(height(root->left), height(root->right));
    }

    void fill(TreeNode* root, vector<vector<string>>&res, const int& height,  int ind, int h = 1){
        if(!root) return;
        res[h-1][ind] = to_string(root->val);
        h++;
        fill(root->left, res, height, ind - pow(2, height-h),  h);
        fill(root->right, res, height, ind + pow(2, height-h), h); 
    }
};


class Solution {
public:
    int depth(TreeNode* root) {
        if(root == NULL) return 0;
        return 1 + max(depth(root->left), depth(root->right));
    }
    
    void printIt(vector<vector<string>>& res, TreeNode* root, int start, int end, int depth) {
        if(root == NULL) return;
        int index = start + (end - start)/2;
        res[depth][index] = to_string(root->val);
        printIt(res, root->left, start, index-1, depth+1);
        printIt(res, root->right, index+1, end, depth+1);
    }
    
    vector<vector<string>> printTree(TreeNode* root) {
        int d = depth(root);
        if(d == 0) return {};
        vector<vector<string>> res(d, vector<string>((1 << d) - 1,""));
        printIt(res, root, 0, res[0].size()-1, 0);
        return res;
    }
};
