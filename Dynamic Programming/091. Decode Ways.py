"""
91. Decode Ways
"""
class Solution:
    def numDecodings(self, s):
        if(len(s)) == 0: return 0
        a = [0 for _ in range(len(s)+1)] 
        a[0] = 1
        a[1] = 1 if s[0] != '0' else 0
        for i in range(1,len(s)):
            if s[i] != '0':
                a[i+1] += a[i]
            if 10<=int(s[i-1:i+1])<=26:
                a[i+1] += a[i-1]  
        return a[-1]
