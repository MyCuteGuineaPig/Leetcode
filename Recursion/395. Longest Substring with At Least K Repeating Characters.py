"""
395. Longest Substring with At Least K Repeating Characters

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

"""

class Solution:
    def longestSubstring(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        def helper(start,end):
            map = collections.Counter(s[start:end+1])
            i = start
            res = 0
            while i<=end: 
                if map[s[i]]<k:
                    l = helper(start,i-1)
                    while(i<=end and map[s[i]]<k): i+= 1 
                    if i>end: return l
                    return max(l,helper(i,end))
                i+=1
            return end-start+1
        return helper(0,len(s)-1)  

class Solution:
    def longestSubstring(self, s, k):
        if not s:
            return 0
        for c in set(s):
            if s.count(c) < k:
                return max(self.longestSubstring(t, k) for t in s.split(c))
        return len(s)