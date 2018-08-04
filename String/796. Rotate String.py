"""
796. Rotate String

Example 1:
Input: A = 'abcde', B = 'cdeab'
Output: true

Example 2:
Input: A = 'abcde', B = 'abced'
Output: false
"""

class Solution:
    def rotateString(self, A, B):
        """
        :type A: str
        :type B: str
        :rtype: bool
        """
        if len(A) != len(B):return False
        if A == B: return True
        n = len(A)
        j = 0
        prefix = [0]*n
        for i, v in enumerate(A[1:]):
            while j>0 and A[j]!=v:
                j = prefix[j-1]
            if v == A[j]: j+=1
            prefix[i+1] = j
        i = j = 0
        while j < n:
            while i < n and A[i] == B[(i+j)%n]:
                i+=1
            if i == n: return True
            if i == 0: i = 1
            j += i - prefix[i-1]
            i = prefix[i-1]
        return False


class Solution:
    def rotateString(self, A, B):
        return len(A) == len(B) and A in B+B
