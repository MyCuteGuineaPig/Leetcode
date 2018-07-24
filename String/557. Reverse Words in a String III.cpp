/*
557. Reverse Words in a String III


Given a string, you need to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.

Example 1:
Input: "Let's take LeetCode contest"
Output: "s'teL ekat edoCteeL tsetnoc"
Note: In the string, each word is separated by single space and there will not be any extra space in the string.



*/

class Solution {
public:
    string reverseWords(string s) {
        for(int i = 0; i<s.size(); i++){
            int j = i;
            while(i<s.size() &&s[i]!=' ') i++;
            if (i>j){
                reverse(s.begin()+j, s.begin()+i);
            }
        }
        return s;
    }
};


// Time:  O(n)
// Space: O(1)

class Solution {
public:
    string reverseWords(string s) {
        for (int i = 0, j = 0; j <= s.length(); ++j) {
            if (j == s.length() || s[j] == ' ') {
                reverse(s.begin() + i, s.begin() + j);
                i = j + 1;
            }
        }
        return s;
    }
};

class Solution {
public:
    string reverseWords(string s) {
        size_t front = 0;
        for(int i = 0; i <= s.length(); ++i){
            if(i == s.length() || s[i] == ' '){
                reverse(&s[front], &s[i]);
                front = i + 1;
            }
        }
        
        return s;
    }
};

class Solution {
public:
    string reverseWords(string s) {
        istringstream iss{s};
        auto iter = s.begin();
        for (string word; iss >> word;) {
            iter = copy(word.rbegin(), word.rend(), iter);
            if (iter != s.end())
                ++iter;
        }
        return s;
    }
};