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

"""
w tells the number of ways
v tells the previous number of ways
d is the current digit
p is the previous digit
"""
class Solution:
    def numDecodings(self, s: str) -> int:
        v, w, p = 0, int(s>''), ''
        print(w, s>'')
        for d in s:
            v, w, p = w, (d>'0')*w + (9<int(p+d)<27)*v, d
        return w
