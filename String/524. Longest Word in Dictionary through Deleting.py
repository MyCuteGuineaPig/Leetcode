"""
524. Longest Word in Dictionary through Deleting


Given a string and a string dictionary, 
find the longest string in the dictionary that can be formed by deleting some characters of the given string. 
If there are more than one possible results, return the longest word with the smallest lexicographical order. 
If there is no possible result, return the empty string.

Example 1:
Input:
s = "abpcplea", d = ["ale","apple","monkey","plea"]

Output: 
"apple"
Example 2:
Input:
s = "abpcplea", d = ["a","b","c"]

Output: 
"a"
"""


""""
The built-in function iter() takes an iterable object and returns an iterator.
with state that remembers where it is during iteration,
c in it returns True if the value in the iteration and updates the state to point at the next value
return False when it goes to the end of iteration

"""

class Solution:
    def findLongestWord(self, s, d):
        """
        :type s: str
        :type d: List[str]
        :rtype: str
        """
        def isvalid(s, word):
            it = iter(s)
            return all(w in it for w in word)

        d.sort(key=lambda x: (-len(x),x))
        for word in d:
            if isvalid(s, word):
                return word
        return ""


class Solution:
    def findLongestWord(self, s, d):

        d.sort()
        d.sort(key=len, reverse=True)
        
        for x in d:
            i = 0
            for c in x:
                i = s.find(c, i) + 1
                if i == 0: break
            else:
                return x
        return ''

class Solution:
    def findLongestWord(self, s, d):
        for word in sorted(d, key = lambda w: (-len(w), w)):
            it = iter(s)
            if all(c in it for c in word): return word
        return ''


class Solution:
    def findLongestWord(self, s, d):
        def isvalid(x):
            it = iter(s)
            return all(c in it for c in x)
        return max(sorted(filter(isvalid, d))+ [''], key = len)
    
class Solution:
    def findLongestWord(self, s, d):
        def isvalid(x):
            it = iter(s)
            return all(c in it for c in x)
        return min(filter(isvalid, d) + [''], key = lambda x: (-len(x),x))


class Solution:
    def findLongestWord(self, s, d):
        def isvalid(x):
            it = iter(s)
            return all(c in it for c in x)
        return min(filter(isvalid, d) + [''], key = lambda x: (-len(x),x))

class Solution:
    def findLongestWord(self, s, d):
        best = ''
        for x in d:
            if (-len(x), x) < (-len(best), best):
                it = iter(s)
                if all(c in it for c in x):
                    best = x
        return best

class Solution:
    def findLongestWord(self, s, d):
        def isSubsequence(x):
            it = iter(s)
            return all(c in it for c in x)
        d.sort(key=lambda x: (-len(x), x))
        return next(filter(isSubsequence, d), '')


