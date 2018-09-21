"""
738. Monotone Increasing Digits

Example 1:
Input: N = 10
Output: 9
Example 2:
Input: N = 1234
Output: 1234
Example 3:
Input: N = 332
Output: 299

"""

class Solution:
    def monotoneIncreasingDigits(self, N):
        """
        :type N: int
        :rtype: int
        """
        li = str(N); n = len(li)
        stk = []
        ind = -1
        for i, (prev, cur) in enumerate(zip(li,li[1:])):
            if cur < prev:
                ind = i
                break 
        if ind == -1: return N
        while ind-1>=0 and li[ind] == li[ind-1]: #i, 右面第一个确定的位置
            ind -= 1 
        return int(li[:ind+1])*10**(n-ind-1)-1


class Solution:
    def monotoneIncreasingDigits(self, N):
        s = str(N); n = len(s)
        ind = -1; i = n-2
        while i>=0:
            if s[i+1] < s[i] or s[ind] == s[i] and ind != -1:
                ind = i
            i-=1
        #print(ind, int(s[ind:]))
        return N if ind == -1 else  N - int(s[ind+1:]) - 1 

class Solution:
    def monotoneIncreasingDigits(self, N):
        """
        :type N: int
        :rtype: int
        """
        N = str(N)
        length = posmark = len(N)
        for i in range(length - 1, 0, -1):
            if N[i - 1] > N[i]:
                N = N[:i - 1] + chr(ord(N[i - 1]) - 1) + N[i:]
                posmark = i
        return int(N[:posmark] + '9' * (length - posmark))


class Solution:
    def monotoneIncreasingDigits(self, N):
        if N < 10:
            return N
        ans = 0
        base = 1
        while N != 0:
            d_cur = N % 10
            N = N // 10
            d_pre = N % 10
            if d_cur >= d_pre or N == 0:
                ans += d_cur * base
            else:    
                ans = base * 10 - 1
                N = N - 1
            base *= 10
        return ans

1235533

