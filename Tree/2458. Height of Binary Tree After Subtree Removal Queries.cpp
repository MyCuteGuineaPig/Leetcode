/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        unordered_map<TreeNode*, int> heights;
        unordered_map<int, int> ans;

        function<int(TreeNode*, unordered_map<TreeNode*, int>&)>getHeight = [&](TreeNode* root, unordered_map<TreeNode*, int>& mp){
            return root? (mp[root] = max(getHeight(root->left, mp), getHeight(root->right, mp))+1): 0;
        };

        function<void(TreeNode*, unordered_map<TreeNode*, int>&, unordered_map<int, int>&, int, int)> dfs = [&](TreeNode* root, unordered_map<TreeNode*, int>& heights, unordered_map<int, int>& ans, int maxheight, int l){
            if(!root){
                return;
            }
            ans[root->val] = maxheight;
            dfs(root->left, heights, ans, max(maxheight, l+heights[root->right]), l+1);
            dfs(root->right, heights, ans, max(maxheight, l+heights[root->left]), l+1);
            
        };

        getHeight(root, heights);
        dfs(root, heights, ans, 0, 0);

        vector<int>res;
        for(auto i: queries){
            res.push_back(ans[i]);
        }
        return res;
    }
};



//先preorder 再post order的reverse, 一个structure
class Solution {
public:
    int preOrder(TreeNode* root, unordered_map<int, int>&mp, int maxL, int l){
        if(!root) {
            return 0;
        }
        mp[root->val] = maxL;
        int left = preOrder(root->left, mp, maxL, l+1);
        int right = preOrder(root->right, mp, max(maxL, l + left), l+1);
        return max(left, right)+1;
    }

    int postOrder(TreeNode* root, unordered_map<int, int>&mp, int maxL, int l){
        if(!root) {
            return 0;
        }
        mp[root->val] = max(maxL, mp[root->val]);
        //cout<<"root->val "<<root->val<<" mp " << mp[root->val]<<" maxL" <<maxL<<endl;
        int right = postOrder(root->right, mp, maxL, l+1);
        int left = postOrder(root->left, mp, max(maxL, l + right), l+1);
        return max(left, right) + 1;
    }

    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        unordered_map<int, int>ans;
        preOrder(root, ans, 0, 0);
        postOrder(root, ans, 0, 0);
        vector<int>res;
        for(auto q: queries)
            res.push_back(ans[q]);
        return res;
    }
};

class Solution {
public:
    int preh[100001], posth[100001], maxh;
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        maxh = 0; pre(root, 0);
        maxh = 0; post(root, 0);
        vector<int> res;
        for (int q : queries)
            res.push_back(max(preh[q], posth[q]));
        return res;
    }

    void pre(TreeNode* root, int h) {
        if (!root) return;
        preh[root->val] = maxh; //先update node 避免left tree更新maxh, 把child tree的height update 到node
        //maxh update 比h 晚一步，保证root->left, root->right 的 preh是0
        maxh = max(maxh, h);
        pre(root->left, h + 1); //先run left, left的height 就会到right
        pre(root->right, h + 1);
    }

    void post(TreeNode* root, int h) {
        if (!root) return;
        posth[root->val] = maxh;
        maxh = max(maxh, h);
        post(root->right, h + 1);
        post(root->left, h + 1);
    }
};


//consise by swap
class Solution {
public:
    int seen[100001], maxh;
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        maxh = 0; dfs(root, 0);
        maxh = 0; dfs(root, 0);
        vector<int> res;
        for (int q : queries)
            res.push_back(seen[q]);
        return res;
    }

    void dfs(TreeNode* root, int h) {
        if (!root) return;
        seen[root->val] = max(seen[root->val], maxh);
        maxh = max(maxh, h);
        dfs(root->left, h + 1);
        dfs(root->right, h + 1);
        swap(root->right, root->left);
    }
};


//两个structure, 一个记录左边，一个纪录右边
class Solution {
public:
    unordered_map<int,int> l,r,ans;
    int height(TreeNode* root){
        if(root==NULL) return 0;
        int le = height(root->left);
        int re = height(root->right);
        l[root->val] = le;                 // Storing maximum height in the left side of current node
        r[root->val] = re;                 // Storing maximum height in the right side of current node
        return max(le,re)+1;      
    }
    void fun(TreeNode* root,int MaxSoFar,int depth){
        if(root==NULL) return;

        ans[root->val] = MaxSoFar;
        fun(root->left,max(MaxSoFar,depth+r[root->val]),depth+1);
        fun(root->right,max(MaxSoFar,depth+l[root->val]),depth+1);
    }
    vector<int> treeQueries(TreeNode* root, vector<int>& q) {
        height(root);
        
        fun(root->left,r[root->val],1);               // Calling on left side and passing the maximum height of right side of root
        fun(root->right,l[root->val],1);              // Calling on right side and passing the maximum height of left side of root
        
        vector<int> res(q.size());
        for(int i = 0;i<q.size();i++){
            res[i] = ans[q[i]];
        }
        return res;
    }
};


class Solution {
public:
    vector<int> D;
    int lvl_left = 0;
    int lvl_right = 0;
    void preorderLeft(TreeNode* root, int level){
        if (root == nullptr) return;
        D[root->val] = lvl_left;
        lvl_left = max(level,lvl_left);
        preorderLeft(root->left,level+1);
        preorderLeft(root->right,level+1);
    }
    
    void preorderRight(TreeNode* root, int level){
        if (root == nullptr) return;
        D[root->val] = max(D[root->val], lvl_right);
        lvl_right = max(level,lvl_right);
        preorderRight(root->right,level+1);
        preorderRight(root->left,level+1);
    }
    
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        D.resize(100001,0);
        lvl_left = lvl_right = 0;
        preorderLeft(root,0); preorderRight(root,0);
        int sz = queries.size();
        vector<int> ans(sz,0);
        int i=0;
        for(int val : queries) {
            ans[i++] = D[val];
        }
        return ans;
    } 
};



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int level[100001] = {}, depth[100001] = {};
    int d1[100001] = {}, d2[100001] = {};
    int traverse(TreeNode* n, int l = 0) {
        if (n == nullptr)
            return 0;
        level[n->val] = l;
        depth[n->val] = 1 + max(traverse(n->left, l + 1), traverse(n->right, l + 1));   
        if (d1[l] < depth[n->val]) {
            d2[l] = d1[l];
            d1[l] = depth[n->val];
        } 
        else if (d2[l] < depth[n->val])
            d2[l] = depth[n->val];
        return depth[n->val];
    };
    vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
        traverse(root, 0);
        transform(begin(queries), end(queries), begin(queries), [&](int q){
            int l = level[q];
            return l + (d1[l] == depth[q] ? d2[l] : d1[l]) - 1;
        });
        return queries;
    }
};