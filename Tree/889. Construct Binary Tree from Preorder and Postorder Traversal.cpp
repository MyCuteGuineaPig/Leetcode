/*
889. Construct Binary Tree from Preorder and Postorder Traversal

Return any binary tree that matches the given preorder and postorder traversals.

Values in the traversals pre and post are distinct positive integers.

 

Example 1:

Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
Output: [1,2,3,4,5,6,7]

Note:

1 <= pre.length == post.length <= 30
pre[] and post[] are both permutations of 1, 2, ..., pre.length.
It is guaranteed an answer exists. If there exists multiple answers, you can return any of them.

        1
       / \
      2    3
     / \  / \
    4  5  6  7

Input: pre = [1,3,6,7], post = [6,7,3,1]
             1
            /
           3
          / \
         6  7


*/

/*

preorder 顺序是 root, (left), (right)
postorder 顺序是 (left) (right), root. 
难点是找到 left 和right的边界, 

把postorder的value 对应上index 建立unordered_map;
因为preorder 顺序和recursion 顺序一样，先建立node, 然后走左面，再右面，所以用一个pointer p记录preorder的位置即可，p++

postorder 用两个pointer 规定现在subtree的起点和终点, 终点是postorder的root->val 的index -1  （因为 postorder 顺序是(left) (right), root)
如果start > end表示post order不能继续了，所以停止subtree recursion, 
当left tree generated 完，假如left tree不是null, post ordere的left->val的index + 1就是右侧tree的起点，终点还是postorder 的root->val的index -1 

*/
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        unordered_map<int, int>map;
        for(int i = 0; i<post.size(); i++){
            map[post[i]] = i;
        }   
        int p = 0;
        return helper(pre, map, p, 0, post.size()-1);
    }

    TreeNode* helper(const vector<int>& pre, unordered_map<int, int>& map, int& p, int start, int end){
        if(p == pre.size() || start>end) return nullptr;
        TreeNode *node = new TreeNode(pre[p]);
        int ind = map[pre[p++]];
        node->left = helper(pre, map, p, start, ind-1);
        if(node->left){
            node->right = helper(pre, map, p, map[node->left->val]+1, ind-1);
        }
        return node;
    }
};


/*

preorder 顺序是 root, (left), (right)
postorder 顺序是 (left) (right), root. 
因为不管在哪个subtree, postorder和preorder长度是一样的, 用len表示现在subtree的长度

定义 pre[prestart: prestart+len] 和 post[poststart: poststart+len] 是现在subtree的

如果subtree 的长度小于等于0，返回null, 
如果subtree 的长度等于1， 返回node (val = pre[prestart])
如果subtree 的长度大于1， 那么pre[prestart + 1 ] 是left tree的node, 
    -- 因为postorder 顺序是 left , right + root, 找到left tree 的node，可以获得 tree 的长度
        postorder.indexof(pre[prestart+1]) + 1 = lefttree 的长度, 比如 1的left node 是2, 2在post的index 是2， left tree长度是 2 - 0 + 1 =3 (4,5,2)
        Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
        Output: [1,2,3,4,5,6,7]
    -- left tree 的prestart = prestart +1(root的下一位), poststart 还是poststart,
    -- right tree 的prestart = prestart + L + 1 (L: 跳过left tree,  + 1跳过root val), 
       poststart 是 poststart +L  (post order的顺序是 left, right , root, +L跳过left的部分), 长度是len - L -1 (-1 减去的是root的长度) 
       poststart 的length 或者是 map[pre[prestart]] - poststart - L (map[pre[prestart]] - poststart 是现在subtree的长度(没有算root的))

*/

class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        unordered_map<int, int>map;
        for(int i = 0; i<post.size(); i++){
            map[post[i]] = i;
        }   
        return helper(pre, map, 0, 0, post.size());
    }

    TreeNode* helper(const vector<int>& pre, unordered_map<int, int>& map, int prestart, int poststart, int len){
        if(len<=0) return nullptr;
        TreeNode *node = new TreeNode(pre[prestart]);
        if(len == 1) return node;
        int L = map[pre[prestart+1]] - poststart + 1; //prestart+1是 left tree第一个node, L是left substree的长度
        node->left = helper(pre, map, prestart+1, poststart, L); 
        node->right = helper(pre, map, prestart + L + 1, poststart+ L, len - L -1); //减去的1是现在的root 
        // node->right = helper(pre, map, prestart + L + 1, poststart+ L, map[pre[prestart]] - poststart - L); //减去的1是现在的root 
        return node;
    }
};



/*

I see a lot of solution saying O(N), but actually not.
If it takes already O(N) time to find left part and right right, it could not be O(N).
If it is recursive solution, it should use a hashmap to reduce complexity, otherwise in most cases it has at least average O(NlogN).

Here I share my iterative solution.
We will preorder generate TreeNodes, push them to stack and postorder pop them out.

Loop on pre array and construct node one by one.
stack save the current path of tree.
node = new TreeNode(pre[i]), if not left child, add node to the left. otherwise add it to the right.
If we meet a same value in the pre and post, it means we complete the construction for current subtree. We pop it from stack.


Example 1:

Input: pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
Output: [1,2,3,4,5,6,7]

        1
       / \
      2    3
     / \  / \
    4  5  6  7

    

当没看见post order时候 且left 没有node， 把新的node 放在left，当left 有东西的时候，放在right

postorder 跟tree 生成路径一样，先左，然后右，再回到root
当back->val == postorder 时候表示现在subtree 走完了，需要回去



比如 
[1,2,4,5,6,3,7]
[4,6,5,2,7,3,1]

       1                                node 2 back 1        
      /  \                              node 4 back 2
     2    3                             node 5 back 2
    / \     \                           node 6 back 5
   4  5      7                          node 3 back 1
     /                                  node 7 back 3
     6

case1 : 如果只有left
       preorder 顺序是 : top -> left -> next
       postorder 顺序是 :  left -> top,   到next: left和top -> pop

case2:  如果有left & right:
       preorder 顺序是 : top -> left -> right  -> next 
       postorder 顺序是 :  left ->right -> top,   到right: left->pop, 因top has left, right = top->right, 
                                                 到next: right & top -> pop, 
                                                 
case 3:  如果 只有right, (right 被当做left)
      preorder 顺序是 : top -> right  -> next 
       postorder 顺序是 :  right -> top,       到right:  因top has no left, right = top -> left

cast 4:  无left, 无 right:
    preorder 顺序是 : top  -> next
    postorder 顺序是 :  top                   到 next, top -> pop

*/
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        vector<TreeNode*> s;
        s.emplace_back(new TreeNode(pre[0]));
        for (int i = 1, j = 0; i < pre.size(); ++i) {
            auto node = new TreeNode(pre[i]);
            while (s.back()->val == post[j]) { //preval == post val, 已经到最左侧了
                s.pop_back(), ++j;
            }
            if (s.back()->left == nullptr) {
                s.back()->left = node;
            } else {
                s.back()->right = node;
            }
            s.emplace_back(node);
        }
        return s[0];
    }
};
