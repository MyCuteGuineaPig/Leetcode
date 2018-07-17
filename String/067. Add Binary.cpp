/*
67. Add Binary

Given two binary strings, return their sum (also a binary string).

The input strings are both non-empty and contains only characters 1 or 0.

Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"

*/

class Solution {
public:
    string addBinary(string a, string b) {
        int i = a.size() - 1, j = b.size() -1, carry = 0;
        vector<int>vec;
        while (i >= 0 || j >= 0 || carry >0){
            if(i>=0)  carry += ( a[i] - '0');
            if(j>= 0) carry += (b[j] - '0');
            vec.push_back(carry%2);//生成的是反的顺序的
            carry >>=1 ;
            i--; j--;
        }
        string res;
        transform(vec.rbegin(), vec.rend(), back_inserter(res), [](const int & i){return i+'0';});
        return res;
    }
};

class Solution {
public:
    string addBinary(string a, string b) {
        int i = a.size() - 1, j = b.size() -1, carry = 0;
        string res;
        vector<int>vec;
        while (i >= 0 || j >= 0 || carry >0){
            if(i>=0)  carry += ( a[i] - '0');
            if(j>= 0) carry += (b[j] - '0');
            res+=to_string(carry%2);//生成的是反的顺序的
            carry >>=1 ;
            i--; j--;
        }
        reverse(res.begin(),res.end());
        return res;
    }
};