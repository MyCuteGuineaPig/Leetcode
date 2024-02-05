"""
3. Longest Substring Without Repeating Characters

Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.

Given "bbbbb", the answer is "b", with the length of 1.

Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
"""
#记录start
import collections
class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        dic = collections.defaultdict(lambda:-1)
        res, start = 0, -1
        for i, v in enumerate(s):
            start = max(start, dic[v])
            dic[v] = i
            res = max(res, i - start)
        return res

class Solution:
    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        dic = collections.defaultdict(int)
        start, res = -1, 0 
        for i, v in enumerate(s):
            if v in dic:
                start = max(start, dic[v]) #比如"abba",  第二个a的上次出现位置是0，但是start应该是2，因为b在两个a中间，出现了两回
            res = max(res, i - start)
            dic[v] = i
        return res

#记录len
class Solution:
    def lengthOfLongestSubstring(self, s):
        dic = collections.defaultdict(lambda: -1)
        len, res = 0, 0 
        for i, v in enumerate(s):
            if i - dic[v] < len + 1: #遇到最小的长度，就更新当前长度，#比如"abba",  第二个b的上次出现位置是1，i-len[v] = 1<2, 更新len = 1
                len = i - dic[v]
            else: len += 1
            res = max(res, len)
            dic[v] = i
        return res

#两个pointer
class Solution:
    def lengthOfLongestSubstring(self, s):
        set_ = set()
        p1, res = 0, 0
        for i, v in enumerate(s):
            while v in set_:
                set_.discard(s[p1])
                p1 += 1
            set_ |= {v}
            res = max(len(set_),res)
        return res
