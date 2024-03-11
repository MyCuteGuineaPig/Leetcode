/*
647. Palindromic Substrings

Given a string, your task is to count how many palindromic substrings in this string.

The substrings with different start indexes or end indexes are counted as different substrings even they consist of same characters.

Example 1:
Input: "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".
Example 2:
Input: "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
Note:
The input string length won't exceed 1000.

*/


/*

用manacher 算法，在snew中 p[i]表示以id为中心最长回文，
到i点，res += p[i] /2 即是答案

比如i点为 ‘#’, 则p[i] 必为奇数，因为p[i] - 1 是最长回文, 以#为中心最长回文长度一定是偶数,半径也是偶数，比如 'ab#ba', 回文长度为4, #半径为2， 
    -  如果# 为中心左右没有回文， p[i] = 1, 比如 a # b
    -  如果#为中心两边有回文, p[i] = 3,5,7...  p[i] = 3 (a#a, 以#一个回文，3/2 = 1), p[i] = 5 ( ab#ba， 可以构成两个以#为中心回文 5/2)
比如i点为 字母, 则p[i] 一定是偶数，因为p[i] - i 是最长回文，  以字母为中心的最长回文长度一定是奇数 比如abcba, 
    -  如果字母 为中心左右没有回文， p[i] = 2， 比如 a # b # c, p[b] = 2, 以b为中心可以构成一个回文， 2/2 = 1
    -  如果字母 为中心有回文, p[i] = 4, 6, 8, 比如 # a # c # a #, 以c为半径, p[c] = 4, 以c为半径可以构成两个回文, a c a 和 c
        比如 # a # c # b # c # a #, 以b为半径, p[b] = 6, 以b为半径可以构成三个回文, a c b c a 和 c b c 和 b

比如 # a #  p[a] = 2

  "#a # b # b # a #"
    1   1 4 1   1
*/


class Solution {
public:
    int countSubstrings(string s) {
        int res = 0;
        string snew = "$#";
        for(int i = 0; i<s.size(); i++){
            snew += s[i];
            snew += "#";
        }
        snew += "^";
        
        
        //manacher
        int id = 0, mx = 0; 
        vector<int>p(snew.size());
        for(int i = 1; i<snew.size()-1; i++){
            if(i<mx){
                p[i] = min(p[2*id - i], mx - i);
            }else
                p[i] = 1;
            while(snew[i+p[i]] == snew[i-p[i]])
                p[i]++;
            res += p[i] / 2;
            if(mx < i+p[i])
            {
                mx = i+p[i];
                id = i;
            }
        }
        return res;
    }
    
    
};


/*
. There are 2N-1 possible centers for the palindrome: we could have a center at S[0], between S[0] and S[1], 
at S[1], between S[1] and S[2], 
at S[2], between S[2] and S[3]etc.
*/
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        int res = 0;
        for(int i = 0; i < 2*n-1; ++i){
            int left = i / 2;
            int right = left + i % 2;
            while (left >= 0 && right < n && s[left] == s[right]){
                --left; 
                ++right;
                ++res;
            }
        }
        return res;
    }
};


//brute force
class Solution {
public:
    int countSubstrings(string s) {
        int sLen = s.length(), cnt = 0, left = 0, right = 0;
        for (int i = 0; i < sLen; i++)
        {
            left = i; right = i;
            while (left >= 0 && right < sLen && s[left] == s[right])
            {
                cnt++;
                left--;
                right++;
            }
            left = i; right = i + 1;
            while (left >= 0 && right < sLen && s[left] == s[right])
            {
                cnt++;
                left--;
                right++;
            }
        }
        return cnt;
    }
};


/*

DP 

dp[i][j] 记录i，j点是不是substring， 
    - 如果s[i] == s[j], 如果 j - i < 3 比如 a, aa, aba,  
    - 或者 dp[i+1][j-1] == true，比如 a[...true....]a，
    则dp[i][j] 为true

    // 3. tabulation
    // time: O(n ^ 2)
    // space: O(n ^ 2)
*/

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        vector<vector<bool>>dp(n, vector<bool>(n));
        //manacher
        int res = 0;
        for(int i = n-1; i>=0; i--){
            for(int j = i; j<n; j++){
                dp[i][j] =  s[i] == s[j] && (j - i < 3 ||dp[i+1][j-1]);
                if(dp[i][j]) res ++;
            }
        }
        return res;
    }
};

//bottom up
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        vector<vector<int>>dp(n, vector<int>(n));
        int res = 0;
        for(int i = 0; i<n; ++i){
            for(int j = 0; j<=i; ++j){
                if (i == j){
                    dp[j][i] = 1;
                } else if (i == j + 1){
                    dp[j][i] =  s[i] == s[j];
                } else{
                    dp[j][i] =  s[i] == s[j] && dp[j+1][i-1];
                }
                res += dp[j][i] ? 1: 0;
            } 
        }
        return res;
    }
};


class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        vector<vector<int>>dp(n, vector<int>(n));
        helper(s, 0, n-1, dp);
        int res =  0;
        for(auto d: dp)
            for (auto c: d)
                res += c;
        return res;
    }

    int helper(const string& s, int i, int j, vector<vector<int>>&dp){
        if (j < 0 || i > s.size() || j < i) {
            return 0;
        }
        if (i == j) {
            return dp[i][j] = 1;
        }
        else if (i + 1 == j && s[i] == s[j]){
            return dp[i][j] == 1;
        }
        else if (dp[i][j]){
            return dp[i][j];
        }
        return dp[i][j] = helper(s, i+1, j - 1, dp) || helper(s, i, j - 1, dp) || helper(s, i+1, j, dp);
    }
};

//
class Solution {
public:
    int countSubstrings(string& s) {
       return memoization(s);
    }
    
    // 2. memoization
    // Time: O(n ^ 2)
    // space: O(n ^ 2)
    int memoization(string& s) {
        vector<vector<int>> mem(s.size(), vector<int>(s.size(), -1));
        int count = 0;
        for(int i = 0; i < s.size(); ++i) {
            for(int j = i; j < s.size(); ++j) {
                count += solve(mem, s, i, j);
            }
        }
        return count;
    }
    
    int solve(vector<vector<int>>& mem, string& s, int i, int j) {
        if (i >= j) return 1;
        if (mem[i][j] >= 0) return mem[i][j];
        return mem[i][j] = s[i] == s[j] ? solve(mem, s, i+1, j-1) : 0;
    }
    
};