/*
459. Repeated Substring Pattern

Given a non-empty string check if it can be constructed by taking a substring of it and appending multiple copies of the substring together. You may assume the given string consists of lowercase English letters only and its length will not exceed 10000.
Example 1:
Input: "abab"

Output: True

Explanation: It's the substring "ab" twice.
Example 2:
Input: "aba"

Output: False
Example 3:
Input: "abcabcabcabc"

Output: True

Explanation: It's the substring "abc" four times. (And the substring "abcabc" twice.)


*/

//kmp
class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        vector<int>prefix(s.size());
        int j = 0;
        for(int i = 1; i<s.size(); i++){
            while(j>0 && s[j]!=s[i]) j = prefix[j-1];
            if(s[j] == s[i]) j++;
            prefix[i] = j;
        }
        return prefix.back()!= 0 &&  s.size()%(s.size() - prefix.back()) == 0; //最后一位不能是0，如果是0， s.size() % s.size() == 0
    }
};

/*
Basic idea:

First char of input string is first char of repeated substring
Last char of input string is last char of repeated substring
Let S1 = S + S (where S in input string)
Remove 1 and last char of S1. Let this be S2
If S exists in S2 then return true else false
Let i be index in S2 where S starts then repeated substring length i + 1 and repeated substring S[0: i+1]


Explanation 1:
If the string S has repeated block, it could be described in terms of pattern.
S = SpSp (For example, S has two repeatable block at most)
If we repeat the string, then SS=SpSpSpSp.
Destroying first and the last pattern by removing each character, we generate a new S2=SxSpSpSy.

If the string has repeatable pattern inside, S2 should have valid S in its string.


Explanation 2:
if S is composed of k substrings s, then S1 = S + S should contain 2k substrings. 
Destroying the first and the last character leads to at least (2k - 2) substrings left.

since k >= 2,
2k - 2 >= k
which means that S1[1:-1] should still contain S

*/
class Solution {
public:
    bool repeatedSubstringPattern(string str) 
    {
        return (str + str).substr(1, str.size() * 2 - 2).find(str)!=-1;
    }
};


class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int len = s.size();
        for (int i = 2, t = len; i <= t; ++i) {
            if (t % i == 0) {
                int r = len / i, j;
                for (j = r; j < len; ++j) {
                    if (s[j] != s[j - r]) {
                        break;
                    }
                }
                if (j == len) {
                    return true;
                }
                for (; t % i == 0; t /= i);
            }
        }
        return false;
    }
};