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


here is the process of 11011000:
level 1 : 1 + makeLargestSpecial( 101100) + 0,
level 2 : 10 + 1100.we need to makeLargestSpecial(10) and makeLargestSpecial(1100)
level 3 : makeLargestSpecial(10) will just return 10, and makeLargestSpecial(1100) will return 1100
go back to level 2, we need to sort 10 and 1100, it will be 1100, 10, now we swap once,
go back to level 1, we join them together : 1 1100 10 0, end .


why sub.push_back("1"+makeLargestSpecial(S.substr(beg+1,i-beg-1))+"0"); ?　

The special string must starts with 1 because: Every prefix of the binary string has at least as many 1's as 0's.
The special string must end with 0, because suppose it ends with 1, with the shape 1M1, then the prefix 1M will have more 0 then 1 which violates Every prefix of the binary string has at least as many 1's as 0's.
We use '1' + makeLargestSpecial(S.substr(beg+1,i-beg-1)) + '0' to only recurse the middle part, i.e. M and avoid recursing the start and the end.
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
