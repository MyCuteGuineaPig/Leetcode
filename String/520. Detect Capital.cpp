/*
520. Detect Capital

Given a word, you need to judge whether the usage of capitals in it is right or not.

We define the usage of capitals in a word to be right when one of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.
Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False

*/


class Solution {
public:
    bool detectCapitalUse(string word) {
        int count = count_if(word.begin(), word.end(), [](const char & c){return isupper(c);});
        return count == word.size() || count == 0 || count == 1 && isupper(word[0]);
    }
};


class Solution {
public:
    bool detectCapitalUse(string word) {
        if(word.size() < 2) return true;
        int upper = isupper(word[1]);
        for(int i = 1; i < word.size();i++) if(isupper(word[i]) != upper) return false;
        if(isupper(word[0]) == 0 && upper != 0) return false;
        return true;
    }