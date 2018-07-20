/*
541. Reverse String II

Given a string and an integer k, you need to reverse the first k characters for every 2k characters counting 
from the start of the string. If there are less than k characters left, reverse all of them. 
If there are less than 2k but greater than or equal to k characters, then reverse the first k characters 
and left the other as original.

Example:
Input: s = "abcdefg", k = 2
Output: "bacdfeg"
Restrictions:
The string consists of lower English letters only.
Length of the given string and k will in the range [1, 10000]

*/


class Solution {
public:
    string reverseStr(string s, int k) {
        for(int i = 0; i<s.size(); i+=2*k){
            if(i+k <= s.size()){
                reverse(s.begin()+i, s.begin()+i+k);
            }else
                reverse(s.begin()+i, s.end());
        }
        return s;
    }
};

class Solution {
public:
    string reverseStr(string s, int k) {
        for (int i = 0; i < s.size(); i += 2*k) reverse(s.begin()+i, min(s.begin()+i+k, s.end()));
        return s;
    }
};


class Solution {
public:
    string reverseStr(string s, int k) {
        int p = 0;
        while (p<s.size()) {
            int l = p;
            int r = p + k - 1;
            if (r > s.size()-1)
                r = s.size()-1;
            while (l<r) {
                swap(s[l], s[r]);
                l++;
                r--;
            }
            p+= 2*k;
        }
        return s;
    }
};