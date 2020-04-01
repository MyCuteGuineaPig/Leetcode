
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

class Solution {
public:
    int numDecodings(string s) {
        int p = 1, pp, n = s.size();
        for(int i=n-1;i>=0;i--) {
            int cur = s[i]=='0' ? 0 : p;
            if(i<n-1 && (s[i]=='1'||s[i]=='2'&&s[i+1]<'7')) cur+=pp;
            pp = p;
            p = cur;
        }
        return s.empty()? 0 : p;   
    }
};

//Memoization O(n)
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> mem(n+1,-1);
        mem[n]=1;
        return s.empty()? 0 : num(0,s,mem);   
    }
    int num(int i, string &s, vector<int> &mem) {
        if(mem[i]>-1) return mem[i];
        if(s[i]=='0') return mem[i] = 0;
        int res = num(i+1,s,mem);
        if(i<s.size()-1 && (s[i]=='1'||s[i]=='2'&&s[i+1]<'7')) res+=num(i+2,s,mem);
        return mem[i] = res;
    }
};

//Recursion O(n^2)
class Solution {
public:
    int numDecodings(string s) {
        return s.empty() ? 0: numDecodings(0,s);    
    }
    int numDecodings(int p, string& s) {
        int n = s.size();
        if(p == n) return 1;
        if(s[p] == '0') return 0;
        int res = numDecodings(p+1,s);
        if( p < n-1 && (s[p]=='1'|| (s[p]=='2'&& s[p+1]<'7'))) res += numDecodings(p+2,s);
        return res;
    }
};


class Solution {
public:
    int numDecodings(string s) {
        if (!s.size() || s.front() == '0') return 0;
        // r2: decode ways of s[i-2] , r1: decode ways of s[i-1] 
        int r1 = 1, r2 = 1;

        for (int i = 1; i < s.size(); i++) {
            // zero voids ways of the last because zero cannot be used separately
            if (s[i] == '0') r1 = 0;

            // possible two-digit letter, so new r1 is sum of both while new r2 is the old r1
            if (s[i - 1] == '1' || s[i - 1] == '2' && s[i] <= '6') {
                r1 = r2 + r1;
                r2 = r1 - r2;
            }

            // one-digit letter, no new way added
            else {
                r2 = r1;
            }
        }

        return r1;
    }
};
