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