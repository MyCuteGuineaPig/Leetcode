/*
212. Word Search II

Given a 2D board and a list of words from the dictionary, find all words in the board.

Each word must be constructed from letters of sequentially adjacent cell, 
where "adjacent" cells are those horizontally or vertically neighboring. 
The same letter cell may not be used more than once in a word.

For example,
Given words = ["oath","pea","eat","rain"] and board =

[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]
Return ["eat","oath"].
Note:
You may assume that all inputs are consist of lowercase letters a-z.

*/

class Solution {
    class Trie{
        public:
            Trie *children[26];
            bool leaves;
            int id;
        
            Trie(){
                leaves = false;
                id = -1;
                fill_n(children,26, nullptr);
            }
        
            ~Trie()
            {
                for(int i=0; i<26; ++i) delete children[i];
            }
    };
    
public:
    void insertWord(Trie * root, const string& word, int index){
        for(int i = 0; i<word.size();i++){
            if(root->children[word[i]-'a'] == nullptr)
                root->children[word[i]-'a'] = new Trie();
            root = root->children[word[i]-'a'];
        }
        root->leaves = true;
        root->id = index;                       
    }
    
    
    Trie *constructTrie(vector<string>& words){
        Trie * trie = new Trie();
        for(int i = 0; i<words.size();i++)
            insertWord(trie, words[i], i);
        return trie;
    }
    
                               
    void dfs(vector<vector<char>>& board, vector<string>& words, Trie * root, vector<string>&res, int i, int j){
        if(i<0 || j<0 || i>=board.size()||j>=board[0].size() || board[i][j] == 'X' || root->children[board[i][j]-'a'] == nullptr)
            return;
        
        root = root->children[board[i][j]-'a'];
        if(root->leaves){
            //cout<<" push back "<<endl;
            res.push_back(words[root->id]);
            root->leaves = false;
        }
        
        char temp = board[i][j];
        board[i][j] = 'X';
        dfs(board,words,root,res,i-1,j);
        dfs(board,words,root,res,i,j-1);
        dfs(board,words,root,res,i+1,j);
        dfs(board,words,root,res,i,j+1);
        board[i][j] = temp;
    }                           
                               
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string>res;
        if(board.size()==0) return res;
        Trie *trie = constructTrie(words);

        for(int i = 0; i<board.size();i++)
            for(int j = 0; j<board[i].size();j++)
                dfs(board, words, trie,res,i,j);
        delete trie;
        return res;
    }
};



class Solution {
    class Trie{
        public:
            Trie *children[26];
            bool leaves;
            int id;
            
            Trie (){
                leaves = false;
                id = -1;
                fill_n(children, 26, nullptr);
            }
        
            ~Trie(){
                for(int i=0; i<26; ++i) delete children[i];
            }
        
            void insert(vector<string>&words){
                for(int i = 0; i<words.size();i++)
                    insertOne(this,words[i],i);
            }
        
            void insertOne(Trie *root,const string & word, int index){
                for(int i = 0; i<word.size();i++){
                    if(root->children[word[i]-'a'] == nullptr) 
                        root->children[word[i]-'a'] = new Trie();
                    root = root->children[word[i]-'a'];
                }
                root->leaves = true;
                root->id = index;
            }
    };
    
public:       
    void dfs(vector<vector<char>>& board, vector<string>& words, Trie * root, vector<string>&res, int i, int j){
        if(i<0 || j<0 || i>=board.size()||j>=board[0].size() || board[i][j] == 'X' || root->children[board[i][j]-'a'] == nullptr)
            return;

        root = root->children[board[i][j]-'a'];
        if(root->leaves){
            //cout<<" push back "<<endl;
            res.push_back(words[root->id]);
            root->leaves = false;
        }

        char temp = board[i][j];
        board[i][j] = 'X';
        dfs(board,words,root,res,i-1,j);
        dfs(board,words,root,res,i,j-1);
        dfs(board,words,root,res,i+1,j);
        dfs(board,words,root,res,i,j+1);
        board[i][j] = temp;
    }                   
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string>res;
        if(board.size()==0) return res;
        Trie *trie = new Trie();
        trie->insert(words);

        for(int i = 0; i<board.size();i++)
            for(int j = 0; j<board[i].size();j++)
                dfs(board, words, trie,res,i,j);
        delete trie;
        return res;
    }
};