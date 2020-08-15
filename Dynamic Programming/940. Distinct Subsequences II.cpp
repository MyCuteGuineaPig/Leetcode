/**
 * 

  abcaba
  
  第3个新增的是所有 abcab 与 最后一个a结合， 减去可能多算的abca组合 

 */

class Solution {
public:
    int distinctSubseqII(string S) {
        int n = S.size();
        int mod = pow(10,9)+7;
        unordered_map<char,long>dp;
        long cnt = 0;
        for(int i = 0; i < n; ++i){
           if(dp.count(S[i])){
               long tmp = cnt;
               cnt = 2*cnt - dp[S[i]];
               dp[S[i]] = tmp;
           }
           else{
               dp[S[i]] = cnt;
               cnt = 2*cnt + 1;
           }
           cnt = (cnt + mod) % mod;
        }
        return cnt;
    }
};


class Solution {
public:
    int distinctSubseqII(string S) {
        int pos[26] = {}, mod = 1e9 + 7, sum = 1;
        for (auto ch : S) {
            auto old_sum = sum;
            sum = (mod + sum * 2 % mod - pos[ch - 'a']) % mod;
            pos[ch - 'a'] = old_sum;
        } 
        return sum - 1; 
    }  
};


//topDown
class Solution {
public:
    int mod = pow(10,9)+7;
    int distinctSubseqII(string S) {
        unordered_map<char,long>dp;
        return topDown(S,0,dp);
    }
    
    
    long topDown(const string& S, int i, unordered_map<char,long>&dp){
        if(i >= S.size())
            return 0;
        long val = topDown(S, i + 1, dp);
        if(dp.count(S[i])){
           long res =  (2 * val - dp[S[i]])%mod;
           dp[S[i]] = val;
           return  (res+mod)%mod;
        }
        else{
           dp[S[i]] = val;
           return (2*val + 1 + mod)%mod;
        }
    }
};

/*

Init an array endswith[26]
endswith[i] to count how many sub sequence that ends with ith character.


Now we have N = sum(endswith) different sub sequence,
add a new character c to each of them,
then we have N different sub sequence that ends with c.

end[c] = sum(end) + 1 for each character.


Input: "aba"
Current parsed: "ab"

endswith 'a': ["a"]
endswith 'b': ["ab","b"]

Current parsed: "aba"

"a" -> "aa"
"ab" -> "aba"
"b" -> "ba"
"" -> "a"

endswith 'a': ["aa","aba","ba","a"]
endswith 'b': ["ab","b"]
result: 6
 */

class Solution {
public:
    int distinctSubseqII(string S) {
        long endsWith[26] = {}, mod = 1e9 + 7;
        for (char c : S)
            endsWith[c - 'a'] = accumulate(begin(endsWith), end(endsWith), 1L) % mod;
        return accumulate(begin(endsWith), end(endsWith), 0L) % mod;
    }
};

class Solution {
public:
    int distinctSubseqII(string S) {
        int res = 0, added = 0, mod = 1e9 + 7, endsWith[26] = {};
        for (char c : S) {
            added = (res - endsWith[c - 'a'] + 1) % mod;
            res = (res + added) % mod;  // res = res + res -  endsWith[c - 'a'] + 1  = 2*res + 1 - endswith
            endsWith[c - 'a'] = (endsWith[c - 'a'] + added) % mod;
            //endsWith[c - 'a'] = res + 1;, S[i]单个的
        }
        return (res + mod) % mod;
    }
};