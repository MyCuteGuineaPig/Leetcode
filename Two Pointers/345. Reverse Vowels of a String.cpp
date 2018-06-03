/*
345. Reverse Vowels of a String
Write a function that takes a string as input and reverse only the vowels of a string.

Example 1:
Given s = "hello", return "holle".

Example 2:
Given s = "leetcode", return "leotcede".

Note:
The vowels does not include the letter "y".

*/


class Solution {
public:
    string reverseVowels(string s) {
        unordered_set<char>dic = {'a','e','i','o','u','A','E','I','O','U'};
        int i = 0, j = s.size()-1;
        while(i<j){
            while(i<j && dic.find(s[i]) == dic.end()) i++;
            while(i<j && dic.find(s[j]) == dic.end()) j--;
            swap(s[i++],s[j--]);
        }
        return s;
    }
};


class Solution {
public:
    string reverseVowels(string s) {
        unordered_set<char>dic = {'a','e','i','o','u','A','E','I','O','U'};
        int i = 0, j = s.size()-1;
        while(i<j){
            while(i<j && dic.find(s[i]) == dic.end()) i++;
            while(i<j && dic.find(s[j]) == dic.end()) j--;
            if(i<j){
                s[i] ^= s[j];
                s[j] ^= s[i];
                s[i] ^= s[j];
                i++;j--;
            }
        }
        return s;
    }
};


class Solution {
public:
    string reverseVowels(string s) {
        int i = 0, j = s.size() - 1;
        while (i < j) {
            i = s.find_first_of("aeiouAEIOU", i);
            j = s.find_last_of("aeiouAEIOU", j);
            if (i < j) {
                swap(s[i++], s[j--]);
            }
        }
        return s;
    }
};