"""
454. 4Sum II

Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

Output:
2

Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0

"""

class Solution:
    def fourSumCount(self, A, B, C, D):
        dic = collections.Counter([a+b for a in A for b in B])
        return sum([dic[-c-d] for c in C for d in D if -c-d in dic])

class Solution:
    def fourSumCount(self, A, B, C, D):
        """
        :type A: List[int]
        :type B: List[int]
        :type C: List[int]
        :type D: List[int]
        :rtype: int
        """
        dic = collections.defaultdict(int)
        for a in A:
            for b in B:
                dic[a+b]+=1
        res = 0;
        for c in C: 
            for d in D:
                if -c-d in dic:
                    res += dic[-c-d]
        return res