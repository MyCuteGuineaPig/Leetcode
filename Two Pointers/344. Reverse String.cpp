/*
344. Reverse String
Write a function that takes a string as input and returns the string reversed.

Example:
Given s = "hello", return "olleh".

*/


class Solution {
public:
    string reverseString(string s) {
        reverse(s.begin(),s.end());
        return s;
    }
};

class Solution {
public:
    string reverseString(string s) {
        int i = 0, j = s.size()-1;
        while(i<j){
            swap(s[i++],s[j--]);
        }
        return s;
    }
};


class Solution {
public:
    string reverseString(string s) {
        int n=s.size();
        for (int i=0, j=n-1; i<j; ++i, --j) {
            s[i]^=s[j];
            s[j]^=s[i];  //s[j] = s[i]^s[j]^s[j] 等于s[i]
            s[i]^=s[j]; //s[i] = s[i]^s[j]^s[i] //最后一个s[i] 是由s[j]过来的，因为s[j]已经等于s[i]了

            // OR
            //char temp=s[i];
            //s[i]=s[j];
            //s[j]=temp;
        }
        return s;
    }
};