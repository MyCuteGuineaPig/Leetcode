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