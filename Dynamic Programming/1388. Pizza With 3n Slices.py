class Solution:
    def maxSizeSlices(self, slices: List[int]) -> int:
        n = len(slices) // 3
        def linear(arr):
            eat = collections.deque([[0] + [-math.inf]*n] * 2) #加0怕有边界问题 因为 i - 1
            res = 0
            for x in arr:
                eat += [i and max(eat[-1][i], eat[-2][i-1]+x) for i in range(n+1)], #1 and 5, return 5
                eat.popleft()
                res = max(res, eat[-1][n])
            return res
        return max(linear(slices[1:]), linear(slices[:-1]))


class Solution:
    def maxSizeSlices(self, slices: List[int]) -> int:
        n = len(slices) // 3 
        def dp(arr):
            eat = collections.deque([[0,]*n]*2)
            for i, x  in enumerate(arr):
                eat += [ i >= 2*j and max(eat[-1][j], eat[-2][j-1] + x) for j in range(n)],
                eat.popleft()
            return eat[-1][-1]
        return max(dp(slices[:-1]), dp(slices[1:]))


class Solution:
    def maxSizeSlices(self, slices: List[int]) -> int:
        n = len(slices) // 3 
        def dp(arr):
            eat = [[0,]*len(arr) for _ in range(2)]
            for i in range(n):
                for j, x in enumerate(arr):
                    if j >= 2*i:
                        eat[i%2][j] = max(eat[i%2][j-1], eat[(i-1)%2][j-2] + x)
            return eat[len(arr)%2][-1]
        return max(dp(slices[:-1]), dp(slices[1:]))

"""

Why do we check j - i + 1 < k * 2 - 1,
instead of something like (k-1) < j - i +1 <= 3 * k

@caohuicn help explain this part:
Because j - i + 1 is not the number of all the slices that are left.
You might have chosen not to take a slice in a previous step,
then there would be leftovers outside of [i, j].
Now if you take i or j (the start or end slice),
one of the slices your friends take will be outside of [i, j],
so the length of [i, j] is reduced by 2, not 3.
Therefore the minimum number is 2 * k - 1
(the last step only requires one slice).

"""

class Solution:
    def maxSizeSlices(self, A):
        @functools.lru_cache(None)
        def dp(i, j, k, cycle=0):
            # i,j = start,end (inclusive)
            # k = remaining
            # cycle (see comment on cycle variable)
            
            if k == 1:
                # one remaining, calculate immediately
                return max(A[i:j + 1])
            
            if j - i + 1 < k * 2 - 1:  # j - i + 1 = 5 有5个数, k = 3， 可以选取index 0, 2, 4, 就不会return -float''inf
                # not possible because not enough elements remain
                return -float('inf')
            
            return max(A[j] +                 # take last element
                       dp(i + cycle, j - 2,   # dp on i to j-2
                          k - 1),             # one less element left to take
                          # (on the cycle variable)
                          # if the last element of the inital array is taken
                          # you cannot take the first element of the inital array
                       # Alternatively, you choose not to take element j
                       dp(i, j - 1,    # dp on i to j-1
                          k))          # same number of elements to take

        return dp(0, len(A) - 1, # dp on 0 to length-1
                  len(A) // 3,   # number of elements to take
                  1)             # see comment on cycle variable
            
        # lru_cache to reduce search space



class Solution:
    def maxSizeSlices(self, slices: List[int]) -> int:
        @functools.lru_cache(None)
        def dp(i, j, k, firstOne = 0):
            if k == 1: 
                return max(slices[i:j+1])
            if j - i + 1 < 2*k - 1 : 
                return float('-inf')
            return max(slices[i] + dp(i+2, j-firstOne, k-1), dp(i+1, j, k))
        return dp(0, len(slices)-1, len(slices)//3, True)