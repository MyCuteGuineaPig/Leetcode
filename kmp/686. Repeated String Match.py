"""
686. Repeated String Match

Given two strings A and B, 
find the minimum number of times A has to be repeated such that B is a substring of it. If no such solution, return -1.

For example, with A = "abcd" and B = "cdabcdab".

Return 3, because by repeating A three times (“abcdabcdabcd”), 
B is a substring of it; and B is not a substring of A repeated two times ("abcdabcd").



"""

class Solution:
    def repeatedStringMatch(self, A, B):
        """
        :type A: str
        :type B: str
        :rtype: int
        """
        m, n = len(A), len(B)
        prefix = [0]*n
        j = 0
        for i,v in enumerate(B[1:]):
            while j>0 and B[j]!=v: 
                j = prefix[j-1]
            if B[j] == v: j+=1 
            prefix[i+1] = j
        i = j = 0
        while i < m:
            while j<n and A[(i+j)%m] == B[j]:
                j+=1 
            if j == n: 
                return (i+j)//m + (1 if (i+j)%m else 0)
            if j == 0: j = 1
            i += j - prefix[j-1]
            j = prefix[j-1]
            
        return -1

class Solution:
    def repeatedStringMatch(self, A, B):
        C = ""
        for i in range(len(B)//len(A) + 3): 
            if B in C:
                return i
            C += A
        return -1