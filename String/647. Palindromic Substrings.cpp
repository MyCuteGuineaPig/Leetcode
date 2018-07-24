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