"""
556. Next Greater Element III

Example 1:

Input: 12
Output: 21
 

Example 2:

Input: 21
Output: -1
"""



class Solution:
    def nextGreaterElement(self, n):
        """
        :type n: int
        :rtype: int
        """
        s = list(str(n))
        i = len(s)-2
        while i >= 0 and s[i]>=s[i+1]:
            i-=1
        if i == -1: return -1
        j = len(s)-1
        while s[j]<=s[i]:
            j-=1
        s[i], s[j] = s[j], s[i]
        s[i+1:] = s[i+1:][::-1]
        res = int("".join(s))
        return res if -2**31 <= res < 2**31 else -1 
        
class Solution:
    def nextGreaterElement(self, n):
        """
        :type n: int
        :rtype: int
        """
        s = list(map(int, str(n)))
        i = len(s)-1
        while i-1>=0 and s[i]<=s[i-1]:
            i -= 1
            
        if i==0:
            return -1
        
        j = i
        while j+1<len(s) and s[j+1]>s[i-1]:
            j += 1
        
        s[i-1], s[j] = s[j], s[i-1]
        s[i:] = reversed(s[i:])
        ret = int(''.join(map(str, s)))
        
        return ret if ret<=((1<<31)-1) else -1