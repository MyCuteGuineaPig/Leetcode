"""
306. Additive Number

Example 1:

Input: "112358"
Output: true 
Explanation: The digits can form an additive sequence: 1, 1, 2, 3, 5, 8. 
             1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8
Example 2:

Input: "199100199"
Output: true 
Explanation: The additive sequence is: 1, 99, 100, 199. 
             1 + 99 = 100, 99 + 100 = 199

"""

class Solution:
    def isAdditiveNumber(self, num):
        """
        :type num: str
        :rtype: bool
        """
        def helper(i, j, start):
            if start == len(num): return True
            if i> 1 and num[start] == '0' or j> 1 and num[start+i] == '0': return False
            a = int(num[start: start+i])
            b = int(num[start+i: start+i+j])
            c = str(a + b)
            if not num.startswith(c, start+i+j):
                return False
            if start + i + j + len(c) == len(num):
                return True
            if helper(j, len(c), start+i):
                return True
            return False
        
        for i in range(1, len(num)//2+1):
            for j in range(1, len(num)//2+1):
                if helper(i, j, 0):
                    return True
        return False


class Solution:
    def isAdditiveNumber(self, num):
        n = len(num)
        for i, j in itertools.combinations(range(1, n), 2):
            a, b = num[:i], num[i:j]
            if a != str(int(a)) or b != str(int(b)): continue
            while j < n:
                c = str(int(a) + int(b))
                if not num.startswith(c, j): break
                j += len(c)
                a, b = b, c
            if j == n: return True
        return False
                