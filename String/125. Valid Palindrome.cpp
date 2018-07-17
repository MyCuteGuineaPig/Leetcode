/*
125. Valid Palindrome

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

Note: For the purpose of this problem, we define empty string as valid palindrome.

Example 1:

Input: "A man, a plan, a canal: Panama"
Output: true
Example 2:

Input: "race a car"
Output: false
*/

class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0, j = s.size()-1;
        while(i < j )
        {
            while( j > i && !isalnum(s[j])) j--;
            while( i <j && !isalnum(s[i])) i++;
            if(i>=j) return true;
            if(tolower(s[i]) != tolower(s[j])) 
                return false;

            i++; j--;
        }
        return true;
    }
};


// Time:  O(n)
// Space: O(1)
// Iterator solution.
class Solution {
public:    
    bool isPalindrome(string s) {
        auto left = s.begin();
        auto right = prev(s.end());
        while (left < right) { 
            if (!isalnum(*left)) {
                ++left;
            } else if (!isalnum(*right)) {
                --right; 
            } else if (tolower(*left) != tolower(*right)) {
                return false;
            } else {
                ++left, --right;
            }
        }
        return true;
    }
};




class Solution {
private:
    void cleanString(string& s) {
        s.erase(remove_if(s.begin(), s.end(), [] (char &c) {
            return !(isalpha(c) || isdigit(c));
        }), s.end());
    }
    
public:
    bool isPalindrome(string s) {
        cleanString(s);
        
        int n = s.size();
        for (int i = 0; i < n / 2; ++i) {
            if (tolower(s[i]) != tolower(s[n - 1 - i]))
                return false;
        }
        
        return true;
    }
};