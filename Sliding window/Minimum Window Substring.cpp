/*
76. Minimum Window Substring
https://leetcode.com/problems/minimum-window-substring/description/

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".

If there are multiple such windows, you are guaranteed that there will always be only one unique minimum window in S.

*/


class Solution {
public:
    string minWindow(string S, string T) {
    if(S.length()==0 || T.length()==0) return "";
        unordered_map<char, int> m;

        for(auto k: T)
            m[k]++;
        
        int minLen =  INT_MAX, minId = 0, i = -1, j = 0, size = S.length();
        // i 必须是﹣1， 必须initialize size,因为S.length() 返回时size_t 默认为正，
        // -1和size_t 没法比
        int require = T.size();
        while(i<size && j<size){
            if(require){
                i++;
                m[S[i]]--;
                if(m[S[i]]>=0) {
                    require--;
                }
            }
            else{
                if(minLen>i-j+1){
                    minLen = i-j+1;
                    minId = j;
                }
                if(m[S[j]]>=0){
                    require++;
                }
                m[S[j]]++;
                j++;
            }
        }
        return minLen == INT_MAX ? "": S.substr(minId,minLen);
    }
};