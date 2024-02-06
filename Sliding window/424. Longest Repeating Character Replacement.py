"""
424. Longest Repeating Character Replacement

Example 1:

Input:
s = "ABAB", k = 2

Output:
4

Explanation:
Replace the two 'A's with two 'B's or vice versa.
Example 2:

Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
"""

class Solution:
    def characterReplacement(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        dic = collections.defaultdict(int)
        j, curmax = 0, 0
        for i, v in enumerate(s):
            dic[v]+=1
            curmax = max(curmax, dic[v])
            if curmax + k < i - j + 1: 
                dic[s[j]]-=1
                j += 1
        return len(s) - j


class Solution:
    def characterReplacement(self, s, k):
        res = lo = 0
        counts = collections.Counter()
        for hi in range(len(s)):
            counts[s[hi]] += 1
            max_char_n = counts.most_common(1)[0][1]
            while (hi - lo  + 1 > max_char_n + k):
                counts[s[lo]] -= 1
                lo += 1
            res = max(res, hi - lo + 1)
        return res