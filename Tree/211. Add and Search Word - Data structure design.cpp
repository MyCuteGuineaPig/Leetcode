/*
211. Add and Search Word - Data structure design

Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . 
means it can represent any one letter.

Example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
Note:
You may assume that all words are consist of lowercase letters a-z.



*/


struct TrieNode{
    unordered_map<char,TrieNode*>children;
    bool isWord = false;
};

class WordDictionary {
public:
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode* T = root;
        for(auto w: word){
            if(T->children.find(w) == T->children.end()) T->children[w] = new TrieNode();
            T = T->children[w];
        }
        T->isWord = true;
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return searchWord(root, 0, word);
    }
    
    bool searchWord(TrieNode* node, int index, const string& word){
        if(index == word.size()) return node->isWord;
        if(word[index]!='.'){
            if(node->children.find(word[index]) == node->children.end()) return false;
            return searchWord(node->children[word[index]], index+1, word);
        }else{
            for(auto t: node->children){
                if(searchWord(t.second, index+1, word))
                    return true;
            }
        }
        return false;
    }
private:
    TrieNode* root;
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary obj = new WordDictionary();
 * obj.addWord(word);
 * bool param_2 = obj.search(word);
 */




class WordDictionary {
public:
    /** Initialize your data structure here. */
    unordered_map<int,vector<string>>cache;
    WordDictionary() {
        
    }
    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        cache[word.size()].push_back(word);
    }
    
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
         int size = word.size();
         if(cache[size].empty()){
             return false;
         }
         vector<string>&words = cache[size];
        for(int i=0;i<words.size();i++){
            string& src = words[i];
            int j = size-1;
            while(j>=0){
                if((word[j]=='.')||(word[j]==src[j])){
                           
                }else{
                    break;
                }         
                j--;
            }
            if(j<0){
                return true;
            }
        }
        return false;
    }
};




class WordDictionary {
public:
    struct Trie {
        vector<Trie *> child;
        bool isWord;
        Trie() : isWord(false), child(vector<Trie *>(26, nullptr)) {}
    };
    Trie *root;
    WordDictionary() : root(new Trie()) {}

    void addWord(string word) {
        const int size_w = word.size();
        Trie *cur = root;
        for (int i = 0; i < size_w; i++) {
            int index = word[i] - 'a';
            if (!cur->child[index]) cur->child[index] = new Trie();
            cur = cur->child[index];
        }
        cur->isWord = true;
    }

    bool search(string word) {
        return search(word.c_str(), root);
    }
    bool search(const char *ch, TrieNode *cur) {
        if (!cur) return false;
        if (*ch == '\0') return cur->isWord;
        if (*ch != '.') {
            return search(ch+1, cur->child[*ch - 'a']);
        } else {
            for (int i = 0; i <= 25; i++) {
                if (search(ch+1, cur->child[i])) return true;
            }
            return false;
        }
    }
};