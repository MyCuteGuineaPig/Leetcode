"""
870. Advantage Shuffle

Given two arrays A and B of equal size, the advantage of A with respect to B is the number of indices i for which A[i] > B[i].

Return any permutation of A that maximizes its advantage with respect to B.

 

Example 1:

Input: A = [2,7,11,15], B = [1,10,4,11]
Output: [2,11,7,15]
Example 2:

Input: A = [12,24,8,32], B = [13,25,32,11]
Output: [24,32,8,12]
"""

class Solution:
    def advantageCount(self, A, B):
        """
        :type A: List[int]
        :type B: List[int]
        :rtype: List[int]
        """
        B = [[b,i] for i,b in enumerate(B)]
        A.sort()
        B.sort()
        i, j = 0, len(B)-1
        res = [0,]*len(B)
        for a in A:
            if a > B[i][0]: 
                res[B[i][1]] = a
                i+=1 
            else:
                res[B[j][1]] = a 
                j -=1 
        return res 

import heapq
class Solution:
    def advantageCount(self, A, B):
        """
        :type A: List[int]
        :type B: List[int]
        :rtype: List[int]
        """
        B = [[-b,i] for i,b in enumerate(B)]
        A.sort()
        heapq.heapify(B)
        i, j = 0, len(A)-1
        res = [0,]*len(B)
        while B:
            if A[j] > -B[0][0]: 
                res[heapq.heappop(B)[1]] = A[j]
                j-=1 
            else:
                res[heapq.heappop(B)[1]] = A[i] 
                i +=1 
        return res 


class Solution:
    def advantageCount(self, A, B):
        A = sorted(A)
        take = collections.defaultdict(list)
        for b in sorted(B)[::-1]:
            if b < A[-1]: take[b].append(A.pop())
        return [(take[b] or A).pop() for b in B]
