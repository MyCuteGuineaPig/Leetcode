/*
639. Decode Ways II

A message containing letters from A-Z is being encoded to numbers using the following mapping way:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Beyond that, now the encoded string can also contain the character '*', which can be treated as one of the numbers from 1 to 9.

Given the encoded message containing digits and the character '*', return the total number of ways to decode it.

Also, since the answer may be very large, you should return the output mod 109 + 7.

Example 1:
Input: "*"
Output: 9
Explanation: The encoded message can be decoded to the string: "A", "B", "C", "D", "E", "F", "G", "H", "I".
Example 2:
Input: "1*"
Output: 9 + 9 = 18
Note:
The length of the input string will fit in range [1, 105].
The input string will only contain the character '*' and digits '0' - '9'.

*/


class Solution {
public:
    int numDecodings(string s) {
        if(s.size()==0) return 0;
        vector<long long>dp(s.size()+1);
        dp[0] = 1;
        dp[1] = s[0] == '*' ? 9 : (s[0] == '0' ? 0: 1);
        static const long long M = 1000000007;
        for(int i = 1; i<s.size();i++){
            dp[i+1] = s[i] == '*' ? (dp[i]*9)%M: (s[i] != '0' ? dp[i]: 0);
            if(s[i] == '*'){
                if(s[i-1] == '*') dp[i+1] += dp[i-1]*15;
                
                else if(s[i-1] == '1') dp[i+1] += dp[i-1]*9;
                    
                else if(s[i-1]=='2') dp[i+1] += dp[i-1]*6;
            }
            else{
                if(s[i-1]=='*'){
                    if(s[i]>='0' && s[i]<='6' ) dp[i+1] += dp[i-1]*2;
                    else dp[i+1] += dp[i-1];
                }
                else{
                    string two = s.substr(i-1,2);
                    if(two>="10" && two<="26") dp[i+1] += dp[i-1];
                }
            }
            dp[i+1] = dp[i+1]%M;
        }
        return dp[s.size()];
    }
};




class Solution {
public:
    int numDecodings(string s) {
        long mod = 1000000007;
        long endingAny = 1, ending1 = 0, ending2 = 0;
        for (char c: s) {
            long curEndingAny = 0;
            if (c == '*') {
                curEndingAny = 9 * endingAny + 9 * ending1 + 6 * ending2;
                ending1 = endingAny;
                ending2 = endingAny;
            } else {
                curEndingAny = (c == '0'? 0:endingAny) + ending1 + (c <= '6'? ending2:0);
                ending1 = (c == '1'? endingAny:0);
                ending2 = (c == '2'? endingAny:0);
            }
            endingAny = curEndingAny % mod;
            cout<<" curEndingAny "<<curEndingAny<<" ending1 "<<ending1<<"  ending2 "<<ending2<<endl;
        }
        return endingAny;
    }
};


class Solution {
public:
    static const long M = 1e9 + 7;
    int numDecodings(string s) {
        long endingAny = 1, ending1 = 0, ending2 = 0;
        for(char c: s){
            long curEndingAny;
            if(c=='*'){
                curEndingAny = 9*endingAny + 9*ending1 + 6*ending2; 
                ending1 = endingAny;
                ending2 = endingAny;
            }
            else{
                curEndingAny = (c!='0')*endingAny + ending1 + (c<='6')*ending2;
                ending1 = (c=='1')*endingAny;
                ending2 = (c=='2')*endingAny;
            }
            endingAny = curEndingAny%M;
        }
        return endingAny;
    }
};


class Solution 
{
public:
    int numDecodings(string s) 
    {
        long e0 = 1, e1 = 0, e2 = 0, f0, f1, f2, M = 1e9 + 7;
        for (char c : s)
        {
            if (c == '*')
            {
                f0 = 9 * e0 + 9 * e1 + 6 * e2;
                f1 = e0;
                f2 = e0;
            }
            else
            {
                f0 = (c > '0') * e0 + e1 + (c <= '6') * e2;
                f1 = (c == '1') * e0;
                f2 = (c == '2') * e0;
            }
            e0 = f0 % M;
            e1 = f1;
            e2 = f2;
        }
        return e0;
    }
};