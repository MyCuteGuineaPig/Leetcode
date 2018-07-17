/*
151. Reverse Words in a String


Given an input string, reverse the string word by word.

Example:  

Input: "the sky is blue",
Output: "blue is sky the".
Note:

A word is defined as a sequence of non-space characters.
Input string may contain leading or trailing spaces. However, your reversed string should not contain leading or trailing spaces.
You need to reduce multiple spaces between two words to a single space in the reversed string.
Follow up: For C programmers, try to solve it in-place in O(1) space.

*/

class Solution {
public:
    void reverseWords(string &s) {
        // Reverse the whole string first.
        reverse(s.begin(), s.end());

        size_t begin = 0, end = 0, len = 0;
        while ((begin = s.find_first_not_of(" ", end)) != string::npos) {
            if ((end = s.find(" ", begin)) == string::npos) {
                end = s.length();
            }
            // Reverse each word in the string.
            reverse(s.begin() + begin, s.begin() + end);

            // Shift the word to avoid extra space.
            move(s.begin() + begin, s.begin() + end, s.begin() + len);
            len += end - begin;
            s[len++] = ' ';
        }
        if(len > 0)
            s = s.substr(0,len-1);
        else
            s = "";
    }
};



class Solution {
public:
    void reverseWords(string &s) {
        reverse(s.begin(), s.end());
        size_t begin = 0, end = 0, len = 0;
        while((begin = s.find_first_not_of(' ', end)) != string::npos){
            if( (end = s.find_first_of(' ', begin)) == string::npos)
                end =  s.size();
            reverse(s.begin()+begin, s.begin() +end );
            move(s.begin() +begin, s.begin()+end, s.begin()+len);
            len += end - begin;
            s[len++] = ' ';
        }
        if(len > 0)
            s = s.substr(0,len-1);
        else
            s = "";
    }
};


class Solution {
public:
    void reverseWords(string &s) {
        reverse(s.begin(), s.end());
        int storeIndex = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != ' ') {
                if (storeIndex != 0) s[storeIndex++] = ' ';
                int j = i;
                while (j < s.size() && s[j] != ' ') { s[storeIndex++] = s[j++]; }
                reverse(s.begin() + storeIndex - (j - i), s.begin() + storeIndex);
                i = j;
            }
        }
        s.erase(s.begin() + storeIndex, s.end());
    }
}