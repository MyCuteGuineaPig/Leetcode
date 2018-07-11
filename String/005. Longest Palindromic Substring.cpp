/*
005. Longest Palindromic Substring

Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.
Example 1:

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
Example 2:

Input: "cbbd"
Output: "bb"

*/


/*
*/


class Solution {
public:
    string longestPalindrome(string s) {
        int maxlen = 0, start = 0;
        for(int i = 0; i<s.size(); i++){
            int len1 = PalLen(s, i, i);
            int len2 = PalLen(s, i-1, i);
            if(len1 > maxlen){
                maxlen = len1; 
                start = i - maxlen/2;
            }
            if(len2 > maxlen){
                maxlen = len2; 
                start = i - maxlen/2;
            }
        }
        return s.substr(start, maxlen);
    }
    
    int PalLen(const string &s, int i , int j){
        while(i>=0 && j <s.size() && s[i]==s[j]){
            i--; j++;
        }
        return j-i-1;
    }
};

class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        if (s.size() == 1) return s;
        int min_start = 0, max_len = 1;
        for (int i = 0; i < s.size();) {
        if (s.size() - i <= max_len / 2) break;
        int j = i, k = i;
        while (k < s.size()-1 && s[k+1] == s[k]) ++k; // Skip duplicate characters.
        i = k+1;
        while (k < s.size()-1 && j > 0 && s[k + 1] == s[j - 1]) { ++k; --j; } // Expand.
        int new_len = k - j + 1;
        if (new_len > max_len) { min_start = j; max_len = new_len; }
        }
        return s.substr(min_start, max_len);
    }
};