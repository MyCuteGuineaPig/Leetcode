"""
809. Expressive Words

Example:
Input: 
S = "heeellooo"
words = ["hello", "hi", "helo"]
Output: 1
Explanation: 
We can extend "e" and "o" in the word "hello" to get "heeellooo".
We can't extend "helo" to get "heeellooo" because the group "ll" is not extended.
"""

class Solution:
    def expressiveWords(self, S, words):
        """
        :type S: str
        :type words: List[str]
        :rtype: int
        """
        res = 0
        for word in words:
            i = j = 0
            while i<len(S):
                if j<len(word) and S[i] == word[j]:
                    i+=1
                    j+=1
                elif i+1<len(S) and S[i+1] == S[i] and i>0 and S[i] == S[i-1]:
                    i+=1
                elif not (i>1 and S[i] == S[i-1] == S[i-2]):
                    break
                else:
                    i+=1
            if i == len(S) and j == len(word):
                res += 1
        return res




class Solution:
    def expressiveWords(self, S, words):
        def is_stretched(S, W):
            i, j, n, m = 0, 0, len(S), len(W)
            for i in range(n):
                if j < m and S[i] == W[j]:
                    j += 1
                elif S[i-1:i+2] != S[i]*3 != S[i-2:i+1]:
                    return False
            return j == m
        return sum(is_stretched(S, w) for w in words)



import itertools


class Solution(object):
    def expressiveWords(self, S, words):
        """
        :type S: str
        :type words: List[str]
        :rtype: int
        """
        # Run length encoding
        def RLE(S):
            return zip(*[(k, len(list(grp)))
                                  for k, grp in itertools.groupby(S)])

        R, count = RLE(S)
        result = 0
        for word in words:
            R2, count2 = RLE(word)
            if R2 != R:
                continue
            result += all(c1 >= max(c2, 3) or c1 == c2
                          for c1, c2 in zip(count, count2))
        return result