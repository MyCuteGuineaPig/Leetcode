"""
546. Remove Boxes
"""
import collections;
class Solution:
    def removeBoxes(self, boxes):
        """
        :type boxes: List[int]
        :rtype: int
        """
        dp = collections.defaultdict(int)
        def dfs(i,j,k):
            if i>j: return 0
            if dp[(i,j,k)]>0: return dp[(i,j,k)]
            while i<j and boxes[j-1] == boxes[j]:
                k += 1; j-=1;
            dp[(i,j,k)] = (k+1)**2 + dfs(i,j-1,0)
            for x in range(i,j):
                if boxes[x] == boxes[j]:
                    dp[(i,j,k)] = max(dp[(i,j,k)], dfs(i,x,k+1)+dfs(x+1,j-1,0))
            return dp[(i,j,k)]
        return dfs(0, len(boxes)-1, 0)


import collections;
class Solution:
    def removeBoxes(self, boxes):
        """
        :type boxes: List[int]
        :rtype: int
        """
        dp = collections.defaultdict(int)
        def dfs(i,j,k):
            if i>j: return 0
            if i == j: return (k+1)**2
            if dp[(i,j,k)]>0: return dp[(i,j,k)]
            while i<j and boxes[j-1] == boxes[j]:
                k += 1; j-=1;
            dp[(i,j,k)] = (k+1)**2 + dfs(i,j-1,0)
            for x in range(i,j):
                if boxes[x] == boxes[j]:
                    dp[(i,j,k)] = max(dp[(i,j,k)], dfs(i,x,k+1)+dfs(x+1,j-1,0))
            return dp[(i,j,k)]
        return dfs(0, len(boxes)-1, 0)





"""
Let A be the array of boxes.

One natural approach is to consider dp(i, j) = the answer for A[i: j+1]. 
But this isn't flexible enough for divide and conquer style strategies. 
For example, with [1,2,2,2,1], we don't have enough information when investigating things like [1,2,2,2] and [1] separately.

Let dp(i, j, k) = the maximum value of removing boxes 
if we have k extra boxes of color A[i] to the left of A[i: j+1]. (We would have at most k < len(A) extra boxes.) 
Let m <= j be the largest value so that A[i], A[i+1], ... A[m] are all the same color. Because a^2 + b^2 < (a+b)^2, 
any block of contiguous boxes of the same color must be removed at the same time, so in fact dp(i, j, k) = dp(m, j, k+(m-i)).

Now, we could remove the k boxes we were carrying plus box A[i] (value: (k+1)**2),
then remove the rest (value: dp(i+1, j, 0)). Or, for any point m in [i+1, j] with A[i] == A[m], 
we could remove dp(i+1, m-1) first, then [m, j] would have k+1 extra boxes of color A[m] behind, which has value dp(m, j, k+1).

The "i, k = m, k + m - i" part skips order (m-i)*(j-i) calls to dp, 
and is necessary to get this kind of solution to pass in Python.


"""



class Solution:
    def removeBoxes(self, A):
        N = len(A)
        memo = [[[0]*N for _ in range(N) ] for _ in range(N) ]
        
        def dp(i, j, k):
            if i > j: return 0
            if not memo[i][j][k]:
                m = i
                while m+1 <= j and A[m+1] == A[i]:
                    m += 1
                i, k = m, k + m - i
                ans = dp(i+1, j, 0) + (k+1) ** 2
                for m in range(i+1, j+1):
                    if A[i] == A[m]:
                        ans = max(ans, dp(i+1, m-1, 0) + dp(m, j, k+1))
                memo[i][j][k] = ans
            return memo[i][j][k]
        
        return dp(0, N-1, 0)