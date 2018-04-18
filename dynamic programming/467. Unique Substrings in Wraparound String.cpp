/*
467. Unique Substrings in Wraparound String

Consider the string s to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", 
so s will look like this: "...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".

Now we have another string p. Your job is to find out how many unique non-empty substrings of p are present in s.
 In particular, your input is the string p and you need to output the number of different non-empty substrings of p in the string s.

Note: p consists of only lowercase English letters and the size of p might be over 10000.

Example 1:
Input: "a"
Output: 1

Explanation: Only the substring "a" of string "a" is in the string s.
Example 2:
Input: "cac"
Output: 2
Explanation: There are two substrings "a", "c" of string "cac" in the string s.
Example 3:
Input: "zab"
Output: 6
Explanation: There are six substrings "z", "a", "b", "za", "ab", "zab" of string "zab" in the string s.



*/


/***错误解**/
class Solution {
public:
    int findSubstringInWraproundString(string p) {
        if(p.size()==0) return 0;
        vector<int>letters(26,0);
        int len = 1, res = 1;
        letters[p[0] - 'a'] = 1;
        for(int i = 1; i<p.size();i++){
            int cur = p[i] - 'a';
            int prev = p[i-1] - 'a';
            if(prev == cur - 1 || (prev == 25 && cur == 0)){
                len++;
                if(letters[cur] < letters[prev]+len) // 错误
                {
                    res += len; // 这样会多算 比如 abcdefghijklmnopqrstuvwxyza,  到a的时候是27，应该加27，但是27个中第27个就是a，已经算过了一次，所以不行
                    letters[cur] = letters[prev]+len;
                }
            }else{
                len = 1;
                if(letters[cur] == 0){
                    res++;
                    letters[cur] =1;
                }
                    
            }
        }
        return res;
    }
};


class Solution {
public:
    int findSubstringInWraproundString(string p) {
        vector<int>letters(26,0);
        int len = 0, res = 0;
        for(int i = 0; i<p.size();i++){
            int cur = p[i] - 'a';
            if(i>0 && ((p[i-1] - 'a')+1)%26 != cur) len = 0;
            if (++len > letters[cur]) {
                res += len - letters[cur];
                letters[cur] = len;
            }
            
        }
        return res;
        
    }
};