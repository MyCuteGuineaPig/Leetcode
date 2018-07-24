/*
720. Longest Word in Dictionary

Given a list of strings words representing an English Dictionary, 
find the longest word in words that can be built one character at a time by other words in words. 
If there is more than one possible answer, return the longest word with the smallest lexicographical order.

If there is no answer, return the empty string.
Example 1:
Input: 
words = ["w","wo","wor","worl", "world"]
Output: "world"
Explanation: 
The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
Example 2:
Input: 
words = ["a", "banana", "app", "appl", "ap", "apply", "apple"]
Output: "apple"
Explanation: 
Both "apply" and "apple" can be built from other words in the dictionary. 
However, "apple" is lexicographically smaller than "apply".
Note:

All the strings in the input will only contain lowercase letters.
The length of words will be in the range [1, 1000].
The length of words[i] will be in the range [1, 30].

*/

class Solution {
public:
    string longestWord(vector<string>& words) {
        Trie t;
        t.insert(words);
        string res = "";
        for(auto word: words){
            if(t.isWord(word)){
                if(res.size() < word.size() || res.size() == word.size() && word < res)
                    res = word;
            }
        }
        return res;
    }
    
struct Trie{
    unordered_map<char,Trie*>child;
    bool isLeaf= false;

    void insert(const vector<string>& words){
        for(auto w: words){
            Trie *t = this;
            for(auto i: w){
                if(t->child.find(i) == t->child.end()) t->child[i] = new Trie();
                t = t->child[i];
            }
            t->isLeaf = true;
        }
    }
    
    bool isWord(const string& word){
        Trie *t = this;
        for(auto i: word){
            if(t->child.find(i) == t->child.end()) return false;
            t = t->child[i];
            if(!t->isLeaf) return false;
        }
        return true;
    }
};
};



class Solution {
public:
    string longestWord(vector<string>& words) {
        TrieNode trie;
        for (int i = 0; i < words.size(); ++i) {
            trie.Insert(words[i], i);
        }

        // DFS
        stack<TrieNode *> stk;
        for (const auto& node : trie.leaves) {
            if (node) {
                stk.emplace(node);
            }
        }
        
        string result;
        while (!stk.empty()) {
            const auto curr = stk.top(); stk.pop();
            if (curr->isString) {
                const auto& word = words[curr->val];
                if (word.size() > result.size() || (word.size() == result.size() && word < result)) {
                    result = word;
                }
                for (const auto& node : curr->leaves) {
                    if (node) {
                        stk.emplace(node);
                    }
                }
            }
        }
        return result;
    }

private:
    struct TrieNode {
        bool isString;
        int  val;
        vector<TrieNode *> leaves;
        
        TrieNode() : isString{false}, val{0}, leaves(26) {}
        
        void Insert(const string& s, const int i) {
            auto* p = this;
            for (const auto& c : s) {
                if (!p->leaves[c - 'a']) {
                    p->leaves[c - 'a'] = new TrieNode;
                }
                p = p->leaves[c - 'a'];
            }
            p->isString = true;
            p->val = i;
        }
        
        ~TrieNode() {
            for (auto& node : leaves) {
                if (node) {
                    delete node;
                }
            }
        }
    };
};



class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end());
        unordered_set<string> built;
        string res;
        for (string w : words) {
            if (w.size() == 1 || built.count(w.substr(0, w.size() - 1))) {
                res = w.size() > res.size() ? w : res;
                built.insert(w);
            }
        }
        return res;
    }
};


class Solution {
public:
    string longestWord(vector<string>& words) {
        unordered_set<string> s;
        for (auto& str : words) s.insert(str);
        sort(words.begin(), words.end(), [](auto& a, auto& b) {return a.length() == b.length() ? a < b : a.length() > b.length(); });
        for (auto& str : words) {
            bool flag = true;
            for (int i = 1; i < str.length(); i++) {
                if (!s.count(str.substr(0, i))) {
                    flag = false;
                    break;
                }
            }
            if (flag) return str;
        }
        return "";
    }
};