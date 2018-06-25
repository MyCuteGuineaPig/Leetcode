/*
409. Longest Palindrome


Given a string which consists of lowercase or uppercase letters, 
find the length of the longest palindromes that can be built with those letters.

This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.

*/

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int>m;
        for(auto c: s) m[c]++;
        int odd = 0, res = 0;
        for(auto it: m){
            if(it.second & 1) res+= it.second - 1, odd = 1;
            else res += it.second;
        }
        return res + odd;
    }
};



class Solution {
public:
    int longestPalindrome(string s) {
        int odds = 0;
        for (auto c = 'A'; c <= 'z'; ++c) {
            odds += count(s.cbegin(), s.cend(), c) & 1;
        }
        return s.length() - odds + (odds > 0);
    }
};


class Solution {
public:
    int longestPalindrome(string s) {
        vector<int> m(58,0);
        int res = 0;
        
        for(int i = 0; i < s.size(); ++i){
            m[s[i] - 'A']++;    
        }
        
        for(auto it = m.begin(); it != m.end(); ++it){
            res += *it / 2 * 2;
        }
        
        if(res < s.size()){
            res++;
        }
        
        return res;
    }
};


class Solution {
public:
    int longestPalindrome(string s) {
        vector<int>map(128);
        int len = 0;
        for (char c : s) {
            map[c] = !map[c];         // flip on each occurrence, false when seen n*2 times
            if (!map[c]) len+=2;
        }
        if (len < s.length()) len++; // if more than len, atleast one single is present
        return len;
    }
};