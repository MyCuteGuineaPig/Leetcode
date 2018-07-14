"""
318. Maximum Product of Word Lengths

Example 1:

Input: ["abcw","baz","foo","bar","xtfn","abcdef"]
Output: 16 
Explanation: The two words can be "abcw", "xtfn".
Example 2:

Input: ["a","ab","abc","d","cd","bcd","abcd"]
Output: 4 
Explanation: The two words can be "ab", "cd".
Example 3:

Input: ["a","aa","aaa","aaaa"]
Output: 0 
Explanation: No such pair of words.

"""
import functools
class Solution:
    def maxProduct(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        dic = collections.defaultdict(int)
        for w in words:
            temp = functools.reduce(lambda x, y: x | 1<<(ord(y) - 97), w, 0)
            dic[temp] = max(dic[temp], len(w))
        return max([w*v for i, w in dic.items() for j, v in dic.items() if i & j == 0], default = 0)


import functools
class Solution:
    def maxProduct(self, words):
        getkey = lambda w:  functools.reduce(lambda x, y: x | 1<<(ord(y) - 97), w, 0)
        key = functools.reduce(lambda x, y: x+[getkey(y)], words, [])
        return max([len(w)*len(v) for i, w in zip(key,words) for j, v in zip(key,words) if i & j == 0], default = 0)