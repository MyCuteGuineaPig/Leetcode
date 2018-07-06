"""
290. Word Pattern

Example 1:

Input: pattern = "abba", str = "dog cat cat dog"
Output: true
Example 2:

Input:pattern = "abba", str = "dog cat cat fish"
Output: false
Example 3:

Input: pattern = "aaaa", str = "dog cat cat dog"
Output: false
Example 4:

Input: pattern = "abba", str = "dog dog dog dog"
Output: false
"""

class Solution:
    def wordPattern(self, pattern, str):
        """
        :type pattern: str
        :type str: str
        :rtype: bool
        """
        pattern, str = list(pattern), str.split()
        pdic, sdic = collections.defaultdict(), collections.defaultdict()
        for i, v in enumerate(zip(pattern, str)):
            if ( v[0] not in pdic )!= (v[1] not in sdic) or v[0] in pdic and v[1] in sdic and pdic[v[0]]!=v[1]:
                return False
            pdic[v[0]] = v[1]
            sdic[v[1]] = v[0]
        return True


class Solution:
    def wordPattern(self, pattern, str):
        """
        :type pattern: str
        :type str: str
        :rtype: bool
        """
        pattern, str = list(pattern), str.split()
        return len(pattern) == len(str) and len(set(zip(pattern, str))) == len(set(pattern)) == len(set(str))


class Solution:
    def wordPattern(self, pattern, str):
        """
        :type pattern: str
        :type str: str
        :rtype: bool
        """
        pattern, str = list(pattern), str.split()
        return list(map(pattern.index, pattern)) == list(map(str.index, str))

#lambda 与上面的是一样的
class Solution:
    def wordPattern(self, pattern, str):
        f = lambda s: map({}.setdefault, s, range(len(s)))
        return list(f(pattern)) == list(f(str.split()))