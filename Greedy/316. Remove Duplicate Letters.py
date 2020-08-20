"""
316. Remove Duplicate Letters

Example 1:

Input: "bcabc"
Output: "abc"
Example 2:

Input: "cbacdcbc"
Output: "acdb"

"""


class Solution:
    def removeDuplicateLetters(self, s):
        """
        :type s: str
        :rtype: str
        """
        stack = []
        remaining = collections.Counter(s)
        instack = set()
        for i in s: 
            if i not in instack: 
                while stack and i < stack[-1] and remaining[stack[-1]] >= 1:
                    instack.discard(stack.pop())  
                stack.append(i)
                instack|= {i}
            remaining[i] -=1 
        return "".join(stack)


class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        for c in sorted(set(s)):  #比如 "abacb", a index = 0, 后面set 包括了 b,c, a是起点
                                  #比如 "dabacb" a index = 1, 但a 后面没有d, a不能是起点
            suffix = s[s.index(c):]  
            if set(suffix) == set(s):
                return c + self.removeDuplicateLetters(suffix.replace(c, ''))
        return ''

"""
找最右侧的index，如果当前index 小于最右侧的index，表示后面还有可以删除
"""
class Solution:
    def removeDuplicateLetters(self, s):
        rindex = {c: i for i, c in enumerate(s)}
        result = []
        for i, c in enumerate(s):
            if c not in result:
                while result and c < result[-1] and i < rindex[result[-1]]:
                    result.pop()
                result += [c]
        return ''.join(result)

class Solution:
    def removeDuplicateLetters(self, s: str) -> str:
        result = ''
        while s:
            i = min(map(s.rindex, set(s)))
            c = min(s[:i+1])
            result += c
            s = s[s.index(c):].replace(c, '')
        return result

"""
找最小的最右侧的index，如果当前index 小于最右侧的index，

然后在这个范围里面选取最小的element，比如'bcabc', 右侧index b: 3, c = 4, a = 2; 在s[:2+1]找最小的字母是a,

"""
class Solution:    
    def removeDuplicateLetters(self, s):
        result = ''
        while s:
            i = min(map(s.rindex, set(s)))
            c = min(s[:i+1])
            result += c
            s = s[s.index(c):].replace(c, '')
        return result

