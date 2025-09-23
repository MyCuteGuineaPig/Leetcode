/*

139. Word Break

https://leetcode.com/problems/word-break/description/

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words,
 determine if s can be segmented into a space-separated sequence of one or more dictionary words. 
 You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

UPDATE (2017/1/4):
The wordDict parameter had been changed to a list of strings (instead of a set of strings). Please reload the code definition to get the latest changes.



*/


class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n = s.size();
        unordered_map<string>Dict(wordDict.begin(),wordBict.end());
        vector<vector<bool>>dp(n,vector<bool>(n,false));
        for(int i = 0; i<s;i++){
            for(int j = 0; j<=i; j++)
            {
                if(Dict.count(substr(j,i-j+1))>0){
                    dp[j][i] = j== 0 ? true: dp[0][j-1];
                }
            }
        }
        return dp[n][n];
    }
};

//2025
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int n  = s.size();
        unordered_set<string>dict(wordDict.begin(), wordDict.end());
        vector<int>dp(n);
        for(int j = 0; j < n; ++j) {
            for(int i = 0; i <=j && !dp[j]; ++i) {
                string sub = s.substr(i, j-i+1);
                if(dict.count(sub)) {
                    dp[j] = (i == 0) ? 1: dp[i-1];
                }
            }
        }
        return dp[n-1];
    }
};


/*
dp[i] = dp[i] || (j == 0)|| dp[j-1];

dp[i] = dp[i] 代表这次如果已经是true了，不要受这次而影响 比如 S = "leetcode" dict = ["le","etc","tc"]
如果到le etc 是对的，但是要继续loop substring 从etc 变成et, 如果不加这个条件这样 leetc 就是false了，因为lee 不在dict里面，

dp[i] =  (j == 0)|| dp[j-1];
比如 S = "leetcode" dict = ["leet","code"]  
(j == 0) apply for "leet"  then dp[3] = true
dp[j-1] apply for "code" (dp[j-1] = dp[3] = true)

*/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>dict(wordDict.begin(),wordDict.end());
        vector<int>dp(s.size(),0);
        for(int i = 0; i<s.size();i++)
            for(int j = 0; j<=i; j++)
                if(dict.find(s.substr(j,i-j+1))!=dict.end())
                    dp[i] = dp[i] || (j == 0)|| dp[j-1];
        return dp[s.size()-1];
    }
};


/*
进一步优化 for(int j = i; j>=0 && !dp[i]; j--) 先从长度小的substring看，一旦到true，break，减小运行时间，

*/

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string>dict(wordDict.begin(),wordDict.end());
        vector<int>dp(s.size(),0);
        for(int i = 0; i<s.size();i++)
            for(int j = i; j>=0 && !dp[i]; j--)
                if(dict.find(s.substr(j,i-j+1))!=dict.end())
                    dp[i] = (j == 0)|| dp[j-1];
        return dp[s.size()-1];
    }
};




// Suffix Trie + DP
struct Trie{
    unordered_map<char, Trie*>mp;
    bool isleaf = false;
    
    void insert(const string& word){
        Trie* t =  this;
        for(const auto& w: word)
        {
            if(t->mp.find(w) == t->mp.end())
                t->mp[w] = new Trie();
            t = t->mp[w];
        }
        t->isleaf = true;
    }
    
    void search(const string& s, int index, vector<int>&dp){
        Trie * t = this;
        while(index < s.size()){
            if(t->mp.find(s[index]) == t->mp.end())
                break;
            t = t->mp[s[index]];
            if(t->isleaf)
                dp[index+1] = true;
            ++index;
        }
    }
};

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        Trie t;
        for(auto w: wordDict)
            t.insert(w);
        
        int n = s.size();
        vector<int>dp(n+1);
        dp[0] = 1;
        for(int i = 0; i<s.size() && !dp[n]; ++i){
            if(dp[i] && t.mp.count(s[i]))
                t.search(s, i, dp);
        }
        return dp[n];
    }
};



/**
 * BFS
 */
class Solution {
public:
    bool wordBreak(string s, unordered_set<string> &dict) {
    // BFS
        queue<int> BFS;
        unordered_set<int> visited;

        BFS.push(0);
        while(BFS.size() > 0)
        {
            int start = BFS.front();
            BFS.pop();
            if(visited.find(start) == visited.end())
            {
                visited.insert(start);
                for(int j=start; j<s.size(); j++)
                {
                    string word(s, start, j-start+1);
                    if(dict.find(word) != dict.end())
                    {
                        BFS.push(j+1);
                        if(j+1 == s.size())
                            return true;
                    }
                }
            }
        }

        return false;
    }
};


//DFS + memoization
/**
 * 

如果没有Memoization 是 O(2^N)
T(N) = T(N-1) + T(N-2) + ... + T(0)
T(N-1) = T(N-2) + ... + T(0)
T(N) - T(N-1) = T(N-1)
T(N) = 2*T(N-1)
O(2^N)

https://leetcode.com/problems/word-break/discuss/169383/The-Time-Complexity-of-The-Brute-Force-Method-Should-Be-O(2n)-and-Prove-It-Below
 * 
 */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        vector<char> mem(s.size(),-1);
        unordered_set<string>mp(wordDict.begin(), wordDict.end());
        return canBrk(0,s,mp,mem); 
    }
    
    bool canBrk(int start, string& s, unordered_set<string>& wordDict,vector<char>& mem) {
        int n = s.size();
        if(start == n) return 1;
        if(mem[start]!= -1) return mem[start];
        string sub;
        for(int i = start; i<n; i++) 
            if(wordDict.count(sub+=s[i]) && canBrk(i+1,s,wordDict,mem)) 
                return mem[start] = 1; 
        return mem[start] = 0;
    }
};