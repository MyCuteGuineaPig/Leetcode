/*
395. Longest Substring with At Least K Repeating Characters

Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:

Input:
s = "aaabb", k = 3

Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:

Input:
s = "ababbc", k = 2

Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.

*/


class Solution {
public:
    int longestSubstring(string s, int k) {
        return helper(s,0,s.size(),k);
    }
    
    int helper(const string &s, int start, int end, const int &k){
        if(end-start<k) return 0;
        unordered_map<char,int>m;
        for(int i = start; i<end; i++)
            m[s[i]] += 1;
        for(int i = start; i<end; i++){
            if(m[s[i]]<k){
                int j = i+1;
                while(j<end && m[s[j]]<k) j++;
                if(j == end) return helper(s,start, i, k);
                return max(helper(s,start, i, k), helper(s,j,end, k));
                //不能返回 max(i-start, helper(s,j,end,k) 原因是： 比如: ababacb k=3
                // 到c m[s[i]] < 1, i-start = 5-0 = 5, 但是ababa 的a 个数并不满足大于3 
            }
        }   
        return end-start;
    }
};




class Solution {
public:
    int longestSubstring(string s, int k) {
        if(s.size() == 0 || k>s.size()) return 0;
        if(k == 0) return s.size();
        unordered_map<char, int>mp;
        for(auto i: s)
            ++mp[i];
        int i = 0;
        while(i < s.size() && mp[s[i]]>=k) ++i;
        if(i == s.size()) return s.size();
        //不加j，会tle
        int j = i;
        while(j < s.size() && mp[s[j]] < k) ++j;
        return max(longestSubstring(s.substr(0,i),k), longestSubstring(s.substr(j),k));
    }
};




/*
Naive Solution
Sol1: a simple improvement on the naive quaratic solution. The idea is that if a locally longest substr is found, 
there's no need to check substrs overlapping it.
Sol1 can run O(n) times in some cases, but worst case is O(n2). Anyway the C++ run time is 3ms.
*/
int longestSubstring(string s, int k) {
   int max_len = 0;
   for (int first = 0; first+k <= s.size();) {
       int count[26] = {0};
       int mask = 0;
       int max_last = first;
       for (int last = first; last < s.size(); ++last) {
           int i = s[last] - 'a';
           count[i]++;
           if (count[i]<k) mask |= (1 << i);
           else   mask &= (~(1 << i));
           
           if (mask == 0) {
               max_len = max(max_len, last-first+1);
               max_last = last;
           }
       }
       first = max_last + 1;
   }
   return max_len;
}
