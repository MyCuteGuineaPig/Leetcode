"""
394. Decode String

s = "3[a]2[bc]", return "aaabcbc".
s = "3[a2[c]]", return "accaccacc".
s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
"""

class Solution:
    def decodeString(self, s):
        """
        :type s: str
        :rtype: str
        """
        i, pattern, num, n = 0, [""], [], len(s)
        while i<n:
            if s[i].isdigit():
                start = i
                while i<n and s[i].isdigit():
                    i+=1    
                num.append(int(s[start:i]))
                continue
            elif s[i] == '[':
                pattern.append("")
            elif s[i] == ']':
                cur = pattern.pop()*(num.pop())
                pattern[-1]+=cur
            else: 
                pattern[-1]+=s[i]
            i+=1
        return pattern[-1]
    
    
    class Solution:
    def decodeString(self, s: str) -> str:
        stk = []
        nums = []
        cur = ""
        n = 0
        for v in s:
            if v == '[':
                stk.append(cur)
                nums.append(n)
                cur = ''
                n = 0
            elif v == ']':
                cur = cur*nums.pop()
                cur = stk.pop() + cur
            elif v.isdigit():
                n = n* 10 + int(v)
            else:
                cur = cur + v
        return cur
