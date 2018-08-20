/*
208. Implement Trie (Prefix Tree)

Implement a trie with insert, search, and startsWith methods.

Example:

Trie trie = new Trie();

trie.insert("apple");
trie.search("apple");   // returns true
trie.search("app");     // returns false
trie.startsWith("app"); // returns true
trie.insert("app");   
trie.search("app");     // returns true
Note:

You may assume that all inputs are consist of lowercase letters a-z.
All inputs are guaranteed to be non-empty strings.

*/


class Trie {
public:
    /** Initialize your data structure here. */
    Trie() {
        
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* T = this;
        for(auto w : word){
            if(T->child.find(w)==child.end())
                T->child[w] = new Trie();
            T = T->child[w];
        }
        T->isleaf = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie* T = this;
        for(auto w : word){
            if(T->child.find(w)==child.end())
               return false;
            T = T->child[w];
        }
        return T->isleaf;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* T = this;
        for(auto w : prefix){
            if(T->child.find(w)==child.end()) return false;
            T = T->child[w];
        }
        return true;
    }
private:
    unordered_map<char,Trie*>child;
    bool isleaf = false;
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie obj = new Trie();
 * obj.insert(word);
 * bool param_2 = obj.search(word);
 * bool param_3 = obj.startsWith(prefix);
 */



class TrieNode {
public:
    TrieNode* map[26];
    bool isWord = false;
};

class Trie {
private: 
    TrieNode* root;
    
public:
    /** Initialize your data structure here. */
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            if(!node->map[word[i]-'a']){
                TrieNode* temp = new TrieNode();
                node->map[word[i]-'a'] = temp;
            }
            node = node->map[word[i]-'a'];
        }
        node->isWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* node = root;
        for(int i = 0; i < word.length(); i++){
            if(!node->map[word[i]-'a']){
                return false;
            }
            else{
                node = node->map[word[i]-'a'];
            }
        }
        
        return node->isWord;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for(int i = 0; i < prefix.length(); i++){
            if(!node->map[prefix[i]-'a']){
                return false;
            }
            else{
                node = node->map[prefix[i]-'a'];
            }
        }
        
        return true;
    }
};



class TrieNode
{
public:
    TrieNode *next[26];
    bool is_word;
    
    // Initialize your data structure here.
    TrieNode(bool b = false)
    {
        memset(next, 0, sizeof(next));
        is_word = b;
    }
};

class Trie
{
    TrieNode *root;
public:
    Trie()
    {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(string s)
    {
        TrieNode *p = root;
        for(int i = 0; i < s.size(); ++ i)
        {
            if(p -> next[s[i] - 'a'] == NULL)
                p -> next[s[i] - 'a'] = new TrieNode();
            p = p -> next[s[i] - 'a'];
        }
        p -> is_word = true;
    }

    // Returns if the word is in the trie.
    bool search(string key)
    {
        TrieNode *p = find(key);
        return p != NULL && p -> is_word;
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(string prefix)
    {
        return find(prefix) != NULL;
    }

private:
    TrieNode* find(string key)
    {
        TrieNode *p = root;
        for(int i = 0; i < key.size() && p != NULL; ++ i)
            p = p -> next[key[i] - 'a'];
        return p;
    }
};