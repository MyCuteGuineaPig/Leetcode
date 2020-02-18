/*
105. Construct Binary Tree from Preorder and Inorder Traversal

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7

*/



//stack 解
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if(preorder.empty()) return {};
        TreeNode* cur = new TreeNode(preorder[0]), *root = cur;
        stack<TreeNode*>stk;//stk 用来preorder iterative traversal 
        for(int i = 1, j = 0; i<preorder.size(); ++i){ //如果preorder 是 top->left, in order left->top,  不会经过if, 直接返回root
            if(cur->val == inorder[j]){ 
                //不能是preorder[i] == inorder[j] 作为对比条件 因为 preorder top->left->right, inorder: left->right->top
                //left 就不能append 到left
                /*
                //preorder top->left->right, in order 是 left->top->right,
                如果到right, stack 顺序是 left, top, 这样最好cur = top 
               
               //preorder top->right, in order 是 top->right, 
               //到right, stack 是top, pop, cur  =top,  top->right = right
                
                */
                ++j;
                while(!stk.empty() && stk.top()->val == inorder[j]){
                    ++j;
                    cur = stk.top(); stk.pop();
                }
                cur = cur->right = new TreeNode(preorder[i]); 
            }else{
                stk.push(cur);//下面cur->left 会改边这个cur
                cur = cur->left = new TreeNode(preorder[i]);
            }
        }
        return root;
    }
};


//O(1) space 
/*

end 是对比left child 来说的返回点 比如,  ()在当前 function 中end值

                                1   
                    /                  \
                   /                     \ 
                 2 (1)                   9(Inf)
               /      \                  /    \
            /           \               #(9)   \
          /                \                     \
          3(2)              4(1)                  10 (Inf)
      /       \            /  \                   /  \
     5(3)     6(2)    7(4)    8 (1)             #(10) #(INF)
    /  \      /  \     /    \     /  \ 
   #(5) #(3) #(6) #(2) #(7)  #(4) #(8) #(1) 
   
preorder  1 2 3 5 6 4 7 8 9 10
inorder   5 3 6 2 7 4 8 1 9 10 

最底层stop 的顺序等于 inorder的顺序

*/
class Solution {
public:
    TreeNode* helper(const vector<int>& preorder, const vector<int>& inorder, int& p, int& i, int stop)    {
        if(p >= preorder.size()) return nullptr;
        if(inorder[i] == stop){
            ++i;
            return nullptr;
        }
        TreeNode* cur = new TreeNode(preorder[p++]);
        cur->left = helper(preorder, inorder, p, i, cur->val);
        cur->right = helper(preorder, inorder, p, i, stop);
        return cur;
        
    }
    
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int p=0, i = 0;
        return helper(preorder, inorder, p,i, numeric_limits<int>::min());
    }
};


/*

Solution:
Let us look at this example tree.

        _______7______
       /              \
    __10__          ___2
   /      \        /
   4       3      _8
            \    /
             1  11
The preorder and inorder traversals for the binary tree above is:

preorder = {7,10,4,3,1,2,8,11}   
inorder = {4,10,3,1,7,11,8,2}
The crucial observation to this problem is the tree’s root always coincides with the first element in preorder traversal. 
This must be true because in preorder traversal you always traverse the root node before its children. 
The root node’s value appear to be 7 from the binary tree above.

We easily find that 7 appears as the 4th index in the inorder sequence. 
(Notice that earlier we assumed that duplicates are not allowed in the tree, so there would be no ambiguity).
 For inorder traversal, we visit the left subtree first, then root node, and followed by the right subtree. 
 Therefore, all elements left of 7 must be in the left subtree and all elements to the right must be in the right subtree.

We see a clear recursive pattern from the above observation. After creating the root node (7), 
we construct its left and right subtree from inorder traversal of {4, 10, 3, 1} and {11, 8, 2} respectively. 
We also need its corresponding preorder traversal which could be found in a similar fashion. 
If you remember, preorder traversal follows the sequence of root node, left subtree and followed by right subtree. 
Therefore, the left and right subtree’s postorder traversal must be {10, 4, 3, 1} and {2, 8, 11} respectively. 
Since the left and right subtree are binary trees in their own right, we can solve recursively!

We left out some details on how we search the root value’s index in the inorder sequence. How about a simple linear search? 
If we assume that the constructed binary tree is always balanced, 
then we can guarantee the run time complexity to be O(N log N), where N is the number of nodes. 
However, this is not necessarily the case and the constructed binary tree can be skewed to the left/right, which has the worst complexity of O(N2).

A more efficient way is to eliminate the search by using an efficient look-up mechanism such as hash table. 
By hashing an element’s value to its corresponding index in the inorder sequence, we can do look-ups in constant time. 
Now, we need only O(N) time to construct the tree, which theoretically is the most efficient way.


*/


/*
preorder = {7,10,4,3,1,2,8,11}   preorder 第一个肯定作为root，root->left 在inorder 7的左面{4,10,3,1}, root->right 在root->右面{11,8,2}
inorder = {4,10,3,1,7,11,8,2}

同理对于root为10时， 搜索范围是{4,10,3,1}, root->left {4}， root->right 时在10右面是{3,1}

对于root为4时， 搜索范围是{4,}，root->left {}， root->right 时在4右面是{}

同理对于root为3时，root->left {3,1}， root->right 时在3的右面是{1}

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
    unordered_map<int,int>inIndex;
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for(int i = 0; i<inorder.size();i++)
            inIndex[inorder[i]] = i;
        return helper(preorder, 0, 0, inorder.size()-1);
    }
    
    TreeNode* helper(vector<int>& preorder, int prestart, int instart, int inend){
        if(prestart>=preorder.size() || instart > inend) return nullptr;
        int rootval = preorder[prestart];
        TreeNode *root = new TreeNode(rootval);
        root->left = helper(preorder, prestart+1,instart, inIndex[rootval]-1);
        root->right = helper(preorder, prestart+inIndex[rootval]-instart+1,inIndex[rootval]+1,inend );
        return root;
    }
    
};



class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int p = 0, i = 0;
        int end = inorder.size();
        return dfs(preorder, inorder, p, i, end);
    }
    
    TreeNode* dfs(vector<int>& preorder, vector<int>& inorder, int& p, int& i, int end) //end 是上一个preorder的位置, 不用pointer，
    /*
    比如
        [7,10,4,3,1,2,8,11]
        [4,10,3,1,7,11,8,2]
        找10的右侧时，p应该到3，ind=2, end = 0, 因为10的上一个数是pre[0] = 7, 一旦找到7，就要返回出去

        _______7______
       /              \
    __10__          ___2
   /      \        /
   4       3      _8
            \    /
             1  11
    */
    {
        //cout<<" pind "<<p<<" ind "<<i<<" end "<<end<<endl;
        if(i < inorder.size() && (end == inorder.size() || inorder[i] != preorder[end]))
        {
            //cout<<" in "<<" preorder "<<preorder[p]<<" inorder "<<inorder[i]<<endl;
            TreeNode* ret = new TreeNode(preorder[p++]);
            ret->left = dfs(preorder, inorder, p, i, p-1);
            ++i;//跨越inorder 现在preorder = inorder 那个元素
            //cout<<" right in "<<" preorder "<<preorder[p-1]<<" inorder "<<inorder[i]<<endl;
            ret->right = dfs(preorder, inorder, p, i, end);
            return ret;
        }
        else return NULL;
    }
};



/*
The idea is as follows:

Keep pushing the nodes from the preorder into a stack (and keep making the tree by adding nodes to the left of the previous node) 
until the top of the stack matches the inorder.

At this point, pop the top of the stack until the top does not equal inorder (keep a flag to note that you have made a pop).

Repeat 1 and 2 until preorder is empty. The key point is that whenever the flag is set, insert a node to the right and reset the flag.

*/

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode *ptr=NULL,*pp=NULL;
        int i=0,j=0;
        TreeNode *root=new TreeNode(0);
        stack<TreeNode*> sn;
        sn.push(root);
        while(j<inorder.size()){
            if(sn.top()->val==inorder[j]){
                pp=sn.top();
                sn.pop();
                j++;
            }
            else if(pp){ //代表这个点刚loop through left part, 该loop through 右边
                ptr=new TreeNode(preorder[i]);
                pp->right=ptr;
                pp=NULL;
                sn.push(ptr);
                i++;
            }
            else{
                ptr=new TreeNode(preorder[i]);
                sn.top()->left=ptr;
                sn.push(ptr);
                i++;
            }
        }
        ptr=root->left;delete root;
        return ptr;
    }
};
