/*

97. Interleaving String
https://leetcode.com/problems/interleaving-string/description/

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.


else if(i == 0)
    table[i][j] = ( table[i][j-1] && s2[j-1] == s3[i+j-1]);
else if(j == 0)
    table[i][j] = ( table[i-1][j] && s1[i-1] == s3[i+j-1]);
 else
    table[i][j] = (table[i-1][j] && s1[i-1] == s3[i+j-1] ) || (table[i][j-1] && s2[j-1] == s3[i+j-1] );

*/
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.length()+s2.length()!= s3.length()) return false;
        vector<vector<bool>>dp(s1.length()+1, vector<bool>(s2.length()+1,false));
        dp[0][0] = true;
        for(int i = 1; i<=s1.length();i++){
            if(dp[i-1][0] && s1[i-1] == s3[i-1])
                dp[i][0] = true;
            else 
                break;
        }
        for(int j = 1;j<=s2.length();j++){
            if(dp[0][j-1] && s2[j-1] == s3[j-1])
                dp[0][j] = true;
            else 
                break;
        }
        for(int i = 1; i<=s1.length();i++){
            for(int j = 1; j<=s2.length();j++){
                dp[i][j] = ( dp[i-1][j] && s1[i-1] == s3[j+i-1]) || ( dp[i][j-1] && s2[j-1] == s3[j+i-1]);
            }
        }
        return dp[s1.length()][s2.length()];
    }
};


public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.length()+s2.length() != s3.length()) return false;
        vector<int>dp(s2.length()+1,0);
        for(int i = 0; i<=s1.length();i++)
            for(int j = 0; j<=s2.length();j++) 
                dp[j] =  (i>0 && s1[i-1] == s3[i+j-1] && dp[j] ) || (j>0 && s2[j-1] == s3[i+j-1] && dp[j-1]) || (i==0 && j==0);
        //(i==0 && j==0) initial position is zero
        //s1[i-1] == s3[i+j-1] 代表s3[i+j-1] 来自S1 
        //s2[j-1] == s3[i+j-1] 代表 s3[i+j-1] 来自S2
        return dp[s2.length()];
    }
};



//DFS with momization
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size())
            return false;
        unordered_set<int>st;
        return dfs(s1,s2,s3,0,0,st);
    }
    
    bool dfs(const string&s1, const string&s2, const string&s3, int i, int j, unordered_set<int>&st){
        if(i+j == s3.size())
            return true;
        if(st.count(i*2*s1.size() + j)){
            return false;
        }
        if(i < s1.size() && s1[i] == s3[i+j] && dfs(s1,s2,s3,i+1, j, st))
            return true;
        if(j < s2.size() && s2[j] == s3[i+j] && dfs(s1,s2,s3, i, j+1, st))
            return true;
        st.insert(i*s1.size()*2 + j);
        return false;
    }
};
