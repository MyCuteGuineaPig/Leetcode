
/*
91. Decode Ways
https://leetcode.com/problems/decode-ways/description/

A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

For example,
Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

The number of ways decoding "12" is 2.

*/


/*
I used a dp array of size n + 1 to save subproblem solutions. 
dp[0] means an empty string will have one way to decode, 
dp[1] means the way to decode a string of size 1. 
I then check one digit and two digit combination and 
save the results along the way. In the end, dp[n] will be the end result.

public class Solution {

*/
class Solution {
public:
    int numDecodings(string s) {
        if(s=="") return 0;
        int n = s.length();
        vector<int>dp(n+1,0);
        dp[0] = 1;
        dp[1] = s[0] != '0' ? 1 :0;
        for(int i = 2; i<=n; i++){
            string one = s.substr(i-1,1);
            string two = s.substr(i-2,2);
            if(one>="1" && one<="9")
                dp[i] += dp[i-1];
            if(two>="10" && two<="26")
                dp[i] += dp[i-2];
        }
        return dp[n];
    }
};