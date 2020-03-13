class Solution:
    def generateTheString(self, n: int) -> str:
        if not n:
            return ''
        if n == 1:
            return 'a'
        if n % 2 == 0:
            return 'a'*(n-1) + 'b'
        return 'a'*n
        
class Solution:
    def generateTheString(self, n):
        return 'b' + 'ab'[n & 1] * (n - 1)