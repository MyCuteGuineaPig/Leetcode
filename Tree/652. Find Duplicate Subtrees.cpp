/*
652. Find Duplicate Subtrees

Given a binary tree, return all duplicate subtrees. For each kind of duplicate subtrees, 
you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with same node values.

Example 1:

        1
       / \
      2   3
     /   / \
    4   2   4
       /
      4
The following are two duplicate subtrees:

      2
     /
    4
and

    4
Therefore, you need to return above trees' root in the form of a list.


*/

/*
对比serialize 的tree 是否出现过，如果只出现过一次，出现过加进结果 
*/
class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, int>lookup;
        vector<TreeNode* >res;
        helper(root,lookup, res);
        return res;
    }

    string helper(TreeNode* root, unordered_map<string, int>& lookup, vector<TreeNode*>&res){
        if(!root) return "";
        string out = to_string(root->val);
        out += "("+helper(root->left, lookup, res)+")";
        out += "("+helper(root->right, lookup, res)+")";
        if(++lookup[out] == 1)
            res.push_back(root);
        return out;  
    }
};



class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        vector<TreeNode*> result;

        findDups(root, result);
        return result;
    }
private:
    unordered_map<int, bool> table;
    unordered_map<long, int> keys;
    
    int findDups(TreeNode* node, vector<TreeNode*>& result )
    {
        if(node == nullptr)
        {
            return 0;
        }
        // use key to id subtree, there one to one relationship between tree values and structure and the key
        // must cast to long first and then shift, otherwise will shift as int and lose data
        long key = static_cast<long>(node->val)<<32;
        int lid = findDups(node->left, result);
        int rid = findDups(node->right, result);
        key |=lid<<16;
        key |=rid;
        
        if(keys.find(key)==keys.end())
              keys.emplace(key,keys.size()+1); //给一个id
        
        int id = keys[key];
        if(table.find(id)==table.end()){ //第一次出现
            table.emplace(id,false);
        }
        else if(table[id] == false) //第二次出现，表示重复，但是如果第三次出现，不放result里面
        {
            result.push_back(node);
            table[id]=true;
        }
        return id;
    }
};


class Solution {
public:
    
    vector<TreeNode*> res;
    
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string, int> m;
        dfs(root, m);
        return res;
    }
    
    string dfs(TreeNode* root, unordered_map<string, int>& m) {
        string s;
        if(root) {
            s = to_string(root->val) + "," + dfs(root->left, m) + "," + dfs(root->right, m);
            if(m[s]++ == 1) res.push_back(root);
        }    
        return s;
    }
};


// O(n)
struct Subtree {
    int v;
    int lid; // id for left subtree
    int rid; // id for right subtree
    Subtree(int x, int l, int r) : v(x), lid(l), rid(r) {}
    bool operator==(const Subtree &r) const {
        return v==r.v && lid==r.lid && rid==r.rid;
    }
};
struct Hasher {
    size_t operator() (const Subtree& k) const{
        size_t key=k.v;
        return (key<<32)+(k.lid^k.rid);
    }
  };   
struct Comp {
    bool operator() (const Subtree& l, const Subtree& r) const {
        return l.v==r.v && l.lid==r.lid && l.rid==r.rid;
    }
  };

class Solution {
public:     
    unordered_map<Subtree, int, Hasher, Comp> fmap; // Subtree=>Subtree id map
    vector<int> count; // id => count map
    vector<TreeNode*> rmap; // subtree id => real root map
    int PostTraverse(TreeNode* root) {
        if (root==NULL)
            return 0;
        int lid = PostTraverse(root->left);
        int rid = PostTraverse(root->right);
        Subtree st(root->val, lid, rid);
        if (fmap.find(st)==fmap.end()) {
            // a new subtree is found
            int newid = count.size(); // new id is always the number of all subtrees traversed
            fmap[st] = newid;
            count.push_back(1);
            rmap.push_back(root);
        } else {
            // this subtree has been found
            count[fmap[st]]++;
        }
        return fmap[st];
    }

    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {       
        fmap[Subtree(INT_MAX,INT_MAX,INT_MAX)] = 0; // id 0 indicates a NULL tree
        count.push_back(1); // count[0] = 1;
        rmap.push_back(NULL); // id 0 indicate null tree
        PostTraverse(root);
        vector<TreeNode*> res;
        for (int i=0; i<count.size(); ++i)
            if (count[i]>1)
                res.push_back(rmap[i]);
        return res;   
    }
};