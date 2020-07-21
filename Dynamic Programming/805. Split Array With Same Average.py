class Solution:
    def splitArraySameAverage(self, A: List[int]) -> bool:
        # A subfunction that see if total k elements sums to target
        # target is the goal, k is the number of elements in set B, i is the index we have traversed through so far
        mem = {}

        def find(target, k, i):
            # if we are down searching for k elements in the array, see if the target is 0 or not. This is a basecase
            if k == 0: return target == 0

            # if the to-be selected elements in B (k) + elements we have traversed so far is larger than total length of A
            # even if we choose all elements, we don't have enough elements left, there should be no valid answer.
            if k + i > len(A): return False

            if (target, k, i) in mem: return mem[(target, k, i)]

            # if we choose the ith element, the target becomes target - A[i] for total sum
            # if we don't choose the ith element, the target doesn't change
            mem[(target - A[i], k - 1, i + 1)] = find(target - A[i], k - 1, i + 1) or find(target, k, i + 1)

            return mem[(target - A[i], k - 1, i + 1)]

        n, s = len(A), sum(A)
        # Note that the smaller set has length j ranging from 1 to n//2+1
        # we iterate for each possible length j of array B from length 1 to length n//2+1
        # if s*j%n, which is the sum of the subset, it should be an integer, so we only proceed to check if s * j % n == 0
        # we check if we can find target sum s*j//n (total sum of j elements that sums to s*j//n)
        return any(find(s * j // n, j, 0) for j in range(1, n // 2 + 1) if s * j % n == 0)    




class Solution:
    def splitArraySameAverage(self, A):
        """
        the average value of A is avg, test all k items's summations, 
        when any k_items_sum == k * avg, return True, else False
        
        for the target k_items_sum and k, we have k_items_sum / k == tot_sum / alen, 
        and k_items_sum must be an integer, k <= len(A) // 2
        so :
            - k_items_sum == tot_sum * k / alen == tot_sum * k // alen
            - tot_sum * k % alen == 0
            - gcd(tot_sum, alen) > 1             # because  k <= len(A) // 2   and  tot_sum * k % alen == 0 
        """
        alen, tot_sum = len(A), sum(A)
        end_k = (alen >> 1) + 1  # only need to test k <= alen//2 items's summations.
        
        P = [1]     # k_items_summation_bitmap
        # P[0] = 1 = 0x1:  stand for  0 items's summation is 0( 0x1 = 2^0)
        
        # P[k] is a bitmap for all k items's summations.  
        # For example, if P[3] == 0x111000,  then all the 3 items's summations can be 3, 4, 5.  (第3,4,5 位bit 是1）     
        # P_i [k] = (P_{i-1} [k - 1] << i) | (P_{i-1} [k])   # A[i] in the k items or not in the k items 
        for i in A:                                         
            P[1:end_k ] = [((p << i) | q) for p, q in zip(P, P[1:end_k ] + [0])]

        """"
        比如 A = [1,2,3,4,5,6]

        A  P 
        1 [1, 2]      (2 = 11), 由一个数组成的可以是 1
        2 [1, 6, 8]     6 = 110, 一个数组成可以是1,2,    8 = 1000, 两个数组成可以是3
        3 [1, 14, 56, 64]   14 = 1110, 一个数组成可以是1,2,3,  56 = 111000, 两个数组成可以是3,4,5    64 = 1000,000, 三个数组成可以是6
        4 [1, 30, 248, 960, 1024]  30 = 111,10  一个数组成可以是1,2,3,4,  248 = 11,111,000, 两个数组成可以是3,4,5,6,7,  960 =1,111,000,000 三个数组成可以是  6,7,8,9
        5 [1, 62, 1016, 8128, 30720, 1024]
        6 [1, 126, 4088, 65472, 520192, 30720, 1024]


        """
            
        for k in range(1, end_k ):    # check k items sub sequence's summations.   
            # for the target k and k_items_sum:
            #   - tot_sum * k % alen == 0 
            #   - k_items_sum == tot_sum * k // alen
            if tot_sum * k % alen == 0 and P[k] & (1 << (tot_sum * k // alen)):
                return True
        return False
"""
NumPy with dynamic programming. 
If B and C have the same average, then that average is also the average of A. 
Looking at it the other way around, I find out whether there's a subsequence of A with the same average as A. 
That will then be B and the rest will be C. So I want the subsequence to be non-empty and not the whole A.

p[n][s] tells me whether it's possible to build a subsequence of size n with sum s.
"""

import numpy as np

import numpy as np
class Solution:
    def splitArraySameAverage(self, A):
        N, S = len(A), sum(A)
        p = np.zeros((N, S+1), dtype=bool)
        p[0][0] = 1
        for a in A:
            p[1:,a:] |= np.array(p[:-1,:-a or None]) #None 的话是有0的时候, p[:-1,:-a or None] = []
        return any(S*n%N == 0 and p[n][S*n//N]
                   for n in range(1, N))

"""
用[2,0,5,6,16,12,15,12,4] 举例
"""
import numpy as np
class Solution:
    def splitArraySameAverage(self, A):
        N, S = len(A), sum(A)
        p = np.zeros((N, S+1), dtype=bool)
        p[~0][~0] = 1 # P[~0][~0] = p[-1][-1]
        for a in A:
            p[:-1,:-a or None] |= p[1:,a:]
        n = np.arange(1, N) #  n = [1 2 3 4 5 6 7 8] 
        s = S * n // N  # s =  [8 16 24 32 40 48 56 64]
        # s * N = s* n = [ True  True  True  True  True  True  True  True]
        # p[-n, -s] =  [False  True  True  True  True  True  True False]
        # (s * N == S * n) & p[~n,~s]:   (必须 s * N = s* n 是true,  p[-n, -s] 也是true )[False  True  True  True  True  True  True False]

        return any((s * N == S * n) & p[~n,~s])


import numpy as np
class Solution:
    def splitArraySameAverage(self, A):
        N, S = len(A), sum(A)
        p = np.zeros(S+1, dtype=int)
        p[~0] = 1
        for a in A:
            p[:-a or None] |= p[a:] << 1
        n = np.arange(1, N)
        s = S * n // N
        return any((s * N == S * n) & (p[~s] >> n))