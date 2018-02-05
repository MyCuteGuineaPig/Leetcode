/*
44. Wildcard Matching

https://leetcode.com/problems/wildcard-matching/description/

Implement wildcard pattern matching with support for '?' and '*'.

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false

*/


/*
dp[i][j] 保存的是 s[0:i) 与 p[0:j) match 不match得结果

else if(p[j] == '*')
    dp[i+1][j+1] = dp[i][j];  *match 一个元素 s[i] = p[j]
    dp[i+1][j+1] = dp[i][j+1] *match 多个元素
    dp[i+1][j+1] =  dp[i+1][j]; *match 不匹配任何元素，s[0:i) 与 p[0:j-1) 匹配，given p[j] == '*';

*/
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<bool>>dp(n+1,vector<bool>(m+1,false));
        dp[0][0] = true;
        
        for(int j = 0; j<m; j++){
            if(dp[0][j] && p[j]=='*') //初始化，比如s = ""  p="**" 结果返回true
                dp[0][j+1] = true;
            else 
                break;
        }
        
        
        for(int j = 0; j<m; j++){
            for(int i = 0; i<n; i++){
                if(s[i]==p[j] || p[j] == '?')
                     dp[i+1][j+1] = dp[i][j];
                else if(p[j] == '*')
                     dp[i+1][j+1] = dp[i][j] || dp[i][j+1] || dp[i+1][j];
            }
        }
        return dp[n][m];
        
    }
};


/*
Using Greedy Algorithm

I agree with dtcxzch. The complexity of the algorithm is O(p*s), where p and s are the lengths of the pattern and input strings. An example of such a worst-case input is:

input: bbbbbbbbbbbb
pattern: *bbbb
*/
class Solution {
public:
    bool isMatch(string s, string p) {
        int n = s.length(), m = p.length(), i = 0, j = 0, asterisk = -1, asteriskMatch = 0;
        while(i<n){
            if(p[j] == '*'){
                asterisk = j; 
                j++;
                asteriskMatch = i; // no forward position, 因为asterisk 可能为空
            }else if(s[i] == p[j] || p[j] == '?'){
                i++;
                j++;
            }else if(asterisk>=0){
                i = asteriskMatch;
                asteriskMatch++; //之前星号代表的，不match了,所以回到星号之前match的下一个
                j = asterisk+1; // 不动星号的位置
            }
            else return false;
        }
        while(j<m && p[j] == '*') j++;
        
        return j==m;
        
    }
};


