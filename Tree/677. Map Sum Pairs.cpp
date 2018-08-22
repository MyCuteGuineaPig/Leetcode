/*
677. Map Sum Pairs

Implement a MapSum class with insert, and sum methods.

For the method insert, you'll be given a pair of (string, integer). 
The string represents the key and the integer represents the value. 
If the key already existed, then the original key-value pair will be overridden to the new one.

For the method sum, you'll be given a string representing the prefix, 
and you need to return the sum of all the pairs' value whose key starts with the prefix.

Example 1:
Input: insert("apple", 3), Output: Null
Input: sum("ap"), Output: 3
Input: insert("app", 2), Output: Null
Input: sum("ap"), Output: 5

*/




class MapSum {
public:
    /** Initialize your data structure here. */
    MapSum() {
        root = new TrieNode();
    }
    
    void insert(string key, int val) {
        TrieNode* cur = root;
        for(auto w: key){
            if(cur->child.find(w) == cur->child.end())
                cur->child[w] = new TrieNode();
            cur = cur->child[w];
            cur->sum += val;
        }
        if(cur->val){
            int temp = cur->val; //减去原来的值，比如现在有apple, app, 更新app，如果直接让cur->val = 新的app val,会忽略apple的值
            cur = root;
            for(auto w: key){
                cur = cur->child[w];
                cur->sum -= temp;
            }
        }
        cur->val = val;
    }
    
    int sum(string prefix) {
        TrieNode* cur = root;
        for(auto w: prefix){
            if(cur->child.find(w) == cur->child.end()) return 0;
            cur = cur->child[w];
        }
        return cur->sum;
    }

private:
    struct TrieNode{
        int sum = 0;
        unordered_map<char, TrieNode*>child;
        int val = 0;
    };
    TrieNode* root;
};




class MapSum {
public:
    /** Initialize your data structure here. */
    MapSum() {
        
    }
    
    void insert(string key, int val) {
        trie_.Insert(key, val);
    }
    
    int sum(string prefix) {
        return trie_.GetCount(prefix);
    }

private:
    struct TrieNode {
        bool isString = false;
        int count = 0;
        int val = 0;
        unordered_map<char, TrieNode *> leaves;
        
        void Insert(const string& s, const int val) {
            const auto delta = val - GetVal(s);
            auto* p = this;
            for (const auto& c : s) {
                if (p->leaves.find(c) == p->leaves.cend()) {
                    p->leaves[c] = new TrieNode;
                }
                p = p->leaves[c];
                p->count += delta;
            }
            p->val = val;
            p->isString = true;
        }

        int GetVal(const string& s) const {
            auto* p = this;
            for (const auto& c : s) {
                if (p->leaves.find(c) == p->leaves.cend()) {
                    return 0;
                }
                p = p->leaves.at(c);
            }
            return p->isString ? p->val : 0;
        }

        int GetCount(const string& s) const {
            auto* p = this;
            for (const auto& c : s) {
                if (p->leaves.find(c) == p->leaves.cend()) {
                    return 0;
                }
                p = p->leaves.at(c);
            }
            return p->count;
        }

        ~TrieNode() {
            for (auto& kv : leaves) {
                if (kv.second) {
                    delete kv.second;
                }
            }
        }
    };
    TrieNode trie_;
};



class MapSum {
public:
    /** Initialize your data structure here. */    
    void insert(string key, int val) {
        mp[key] = val;
    }
    
    int sum(string prefix) {
        int sum = 0, n = prefix.size();
        for (auto it = mp.lower_bound(prefix); it != mp.end() && it->first.substr(0, n) == prefix; it++) 
            sum += it->second;
        return sum;
    }
private:
    map<string, int> mp;
};