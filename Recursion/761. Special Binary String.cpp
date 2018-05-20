/*
761. Special Binary String

*/


/*

Just 4 steps:

Split S into several special strings (as many as possible).
Special string starts with 1 and ends with 0. Recursion on the middle part.
Sort all special strings in lexicographically largest order.
Join and output all strings.
Updated:

The middle part of a special string may not be another special string. But in my recursion it is.
For example, 1M0 is a splitted special string. M is its middle part and it must be another special string.

Because:

The number of 0's is equal to the number of 1's in M
If there is a prefix P of Mwhich has one less 1's than 0's, 1P will make up a special string. 
1P will be found as special string before 1M0 in my solution.
It means that every prefix of M has at least as many 1's as 0's.
*/


class Solution {
public:
    string makeLargestSpecial(string S) {
        vector<string>sub;
        int count = 0;
        for(int i = 0, beg = 0; i<S.size();i++){
            if(S[i]=='1') count++;
            else count--;
            if(count == 0){
                sub.push_back("1"+makeLargestSpecial(S.substr(beg+1,i-beg-1))+"0");
                beg = i+1;
            }
        }
        sort(sub.begin(),sub.end(),greater<string>());
        string res = "";
        for(auto i:sub)
            res += i;
        return res;
    }
};