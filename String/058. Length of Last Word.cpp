/*
58. Length of Last Word

Given a string s consists of upper/lower-case alphabets and empty space characters ' ', return the length of last word in the string.

If the last word does not exist, return 0.

Note: A word is defined as a character sequence consists of non-space characters only.

Example:

Input: "Hello World"
Output: 5

*/


class Solution {
public:
    int lengthOfLastWord(string s) {
        int count = 0;
        int i = s.size()-1;
        while(i>=0 && s[i]==' ') i--;
        int start = i;
        for(; i>=0 && s[i]!=' '; i--);
        return start - i;
    }
};

class Solution {
public:
    int lengthOfLastWord(string s) { 
        int len = 0, tail = s.length() - 1;
        while (tail >= 0 && s[tail] == ' ') tail--;
        while (tail >= 0 && s[tail] != ' ') {
            len++;
            tail--;
        }
        return len;
    }
};

//find if 
class Solution {
public:
    int lengthOfLastWord(string s) {
        const auto is_space = [](const char c) { return isspace(c); };
        const auto it = find_if_not(s.rbegin(), s.rend(), is_space);
        const auto jt = find_if(it, s.rend(), is_space);
        return distance(it, jt);
    }
};

//find if + bind1st
class Solution {
public:
    int lengthOfLastWord(string s) {
        auto start = find_if(s.rbegin(), s.rend(), bind1st(not_equal_to<char>(),' '));
        auto i =  find_if(next(start), s.rend(), bind1st(equal_to<char>(),' '));
        return distance(start,i);
    }
};

//string find_last_not_of + find_last_of
class Solution {
public:
    int lengthOfLastWord(string s) {
        size_t start = s.find_last_not_of(' ');
        if (start == string::npos) return 0;
        if(start == 0) return 1;
        size_t end = s.find_last_of(' ',start-1);
        return start!=string::npos? start - end: 0;//避免"" "
    }
};


 int lengthOfLastWord(const char* s) {
        int len = 0;
        while (*s) {
            if (*s++ != ' ')
                ++len;
            else if (*s && *s != ' ')
                len = 0;
    
        }
        return len;
    }