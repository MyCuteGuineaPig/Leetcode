/*
680. Valid Palindrome II

Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

Example 1:
Input: "aba"
Output: True
Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.
Note:
The string will only contain lowercase characters a-z. The maximum length of the string is 50000.


*/

/*


acbcca
*/


class Solution {
public:
    bool validPalindrome(string s) {
        int i = 0, j = s.size()-1;
        while(i<j){
            if(s[i]!=s[j]){
                return isPal(s, i+1, j) || isPal(s, i, j-1);
            } 
            i++, j--;
        }
        return true;
    }
    
    int isPal(const string & s, int i, int j){
        while(i<j){
            if(s[i]!=s[j]) return false; 
            i++, j--;
        }
        return true;
    }
};

class Solution {
public:
    bool validPalindrome(string s) {
        for (int i = 0, j = s.size() - 1; i < j; i++, j--)
            if (s[i] != s[j]) {
                int i1 = i, j1 = j - 1, i2 = i + 1, j2 = j;
                while (i1 < j1 && s[i1] == s[j1]) {i1++; j1--;};
                while (i2 < j2 && s[i2] == s[j2]) {i2++; j2--;};
                return i1 >= j1 || i2 >= j2;
            }
        return true;
    }
};

class Solution {
public:
    // consider input: "abbza" 
    bool validPalindrome(string s) {
        return checkPalindrome(s, 0, s.size()-1, 1);
    }
    
    bool checkPalindrome(string& str, int s, int e, int allowable_deletion) {
        // cout << s << "\t" << e <<endl;
        if(s >= e) return true;
        
        if(str[s] == str[e])
            return checkPalindrome(str, s+1, e-1, allowable_deletion);
        else 
            return allowable_deletion > 0 
                && (checkPalindrome(str, s+1, e, allowable_deletion-1) || checkPalindrome(str, s, e-1, allowable_deletion-1));
    }
};