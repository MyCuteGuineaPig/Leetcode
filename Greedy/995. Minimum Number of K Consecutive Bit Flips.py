class Solution:
    def minKBitFlips(self, A: List[int], K: int) -> int:
        cur, res, n = 0, 0, len(A)
        for i in range(len(A)):
            if i >= K and A[i - K] > 1:
                A[i - K] -= 2
                cur -= 1
            if cur & 1 ^ A[i] == 0:
                if i + K > len(A):
                    return -1
                A[i] += 2
                cur += 1
                res += 1
        return res



class Solution:
    def minKBitFlips(self, A: List[int], K: int) -> int:
        q = deque()
        res = 0
        for i in range(len(A)):
            if len(q) % 2 != 0:
                if A[i] == 1:
                    res += 1
                    q.append(i+K-1)
            else:
                if A[i] == 0:
                    res += 1
                    q.append(i+K-1)
            if q and q[0] == i: q.popleft()
            if q and q[-1] >= len(A): return -1
        return res

# O(1) space
class Solution:
    def minKBitFlips(self, A: List[int], K: int) -> int:
        res = 0
        flips = 0
        addon = 10
        for i in range(len(A)):
            if (flips % 2 != 0 and (A[i] - addon) % 2 == 1) or (flips % 2 == 0 and (A[i] - addon) % 2 == 0):
                    res += 1
                    if i+K-1 >= len(A): return -1
                    A[i+K-1] += addon
                    flips += 1
            if A[i] > 1: 
                flips -= 1
                A[i] -= addon
        return res