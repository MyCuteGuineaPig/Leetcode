/*
863. All Nodes Distance K in Binary Tree


We are given a binary tree (with root node root), a target node, and an integer value K.

Return a list of the values of all nodes that have a distance K from the target node.  The answer can be returned in any order.

 

Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, K = 2

Output: [7,4,1]

Explanation: 
The nodes that are a distance 2 from the target node (with value 5)
have values 7, 4, and 1.



Note that the inputs "root" and "target" are actually TreeNodes.
The descriptions of the inputs above are just serializations of these objects.
 

Note:

The given tree is non-empty.
Each node in the tree has unique values 0 <= node.val <= 500.
The target node is a node in the tree.
0 <= K <= 1000.


*/

/*

先通过dfs 找到所有双向的路径
再通过bfs，从target 出发发散找到所有距离为k的点
*/
class Solution {
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        unordered_map<int,vector<int>>adj;
        dfs(NULL, root, adj);
        
        vector<int>res{target->val};
        unordered_set<int>visited{target->val};
        for(int i = 0; i<K; i++){
            //cout<<" i "<<i<<endl;
            vector<int>bfs;
            for(auto p: res)
                for(auto next: adj[p])
                    if(visited.count(next) == 0){
                        bfs.push_back(next);
                        visited.insert(next);
                    }
            res = move(bfs);
        }
        return res;
    }
    
    void dfs(TreeNode* parent, TreeNode* root, unordered_map<int,vector<int>>& adj){
        if(!root) return;
        if(parent){
            adj[parent->val].push_back(root->val);
            adj[root->val].push_back(parent->val);
        }
        dfs(root, root->left, adj);
        dfs(root, root->right, adj);
    }
};


class Solution {
    /**
        Use a DFS function to track the distance between the current node and the target node.

        int DFS(TreeNode* root, TreeNode* target, int K, int dis, vector<int>& v)
        The distance variable is to track whether if the target reached. If it is not yet reached,
        distance is -1, else it is the real distance between the current node and target node.
        The function will return the real distance of the current node and the target node after the target is reached.
    */
    int dfs(TreeNode* node, TreeNode* target, int K, int dis, vector<int>& result){
        if (!node) return dis;

        if (node == target) dis = 0;

        int distanceFromLeftNode = dfs(node-> left, target, K, dis == -1 ? -1 : dis + 1, result);
        int distanceFromRightNode = dfs(node-> right, target, K, dis == -1 ? -1 : dis + 1, result);

        if (dis == -1 && (distanceFromLeftNode >= 0 || distanceFromRightNode >= 0)) {
            dis = max(distanceFromLeftNode, distanceFromRightNode) + 1;
            if (distanceFromLeftNode >= 0) {
                ///int temp = dfs(node-> right, target, K, dis + 1, result);
                dfs(node->right, target, K, dis + 1, result);
            }

            if (distanceFromRightNode >= 0) {
                ///int temp = dfs(node-> left, target, K, dis + 1, result);
                dfs(node->left, target, K, dis + 1, result);
            }
        }

        if (dis == K) {
            result.emplace_back(node->val);
        }

        return dis;
    }
public:
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        vector<int> result;
        int h = dfs(root, target, K, -1, result);
        return move(result);
    }
};



class Solution {
public:
    vector<int> ans;   
    map<TreeNode*, TreeNode*> parent;  // son=>parent  
    set<TreeNode*> visit;    //record visied node
    
    void findParent(TreeNode* node){
        if (!node) return;
        if (node->left) {
            parent[node->left] = node;
            findParent(node->left);
        }
        if (node->right) {
            parent[node->right] = node;
            findParent(node->right);
        }
    }
    
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (!root) return {};
        
        // Annotate each node with parent.
        findParent(root);
        
        // Finds K distance childs from target node.
        dfs(target, K);
        
        return ans;
    }
    void dfs(TreeNode* node, int K) {
        if (visit.find(node) != visit.end()) return;
        visit.insert(node);
        if (K == 0){
            ans.push_back(node->val);
            return;
        }
        if (node->left) dfs(node->left, K-1);
        if (node->right) dfs(node->right, K-1);
        
        // This is the key, it will recursively call all parent from target to root.
        // And then same for each child. But they will be already cached at that point.
        TreeNode* p = parent[node];
        if (p) dfs(p, K-1);
    }
};