class Fenwick:
    def __init__(self, n):
        self.n = n
        self.bit = [0]*(n+1)

    def add(self, i, delta):
        i += 1 
        while i <= self.n:
            self.bit[i] += delta
            i += i & -i 

    def prefix_sum(self, i):
        tot = 0 
        i += 1 
        while i > 0:
            tot += self.bit[i]
            i -= i & -i 
        return tot

    def range_sum(self, l, r):
        if l > r:
            return 0
        return self.prefix_sum(r) - self.prefix_sum(l-1)

class Solution:
    def minDeletions(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        s = list(s)

        fw = Fenwick(n-1)
        change = [0 for i in range(n-1)]
        for i in range(n-1):
            change[i] = 1 if s[i] == s[i+1] else 0
        for i in range(n-1):
            fw.add(i, change[i])

        res = []

        for q in queries:
            if q[0] == 1: 
                ind = q[1]
                s[ind] = 'A' if s[ind] == 'B' else 'B'

                for i in (ind-1, ind):
                    if i < 0 or i >= n - 1:
                        continue 
                    new_val = 1 if s[i] == s[i+1] else 0
                    if new_val != change[i]:
                        fw.add(i,  new_val - change[i])
                        change[i] = new_val

            else:
                l, r = q[1], q[2]
                res.append(fw.range_sum(l, r-1))
        return res
    



class FenwickTree:
    def __init__(self, size):
        self.tree = [0] * (size + 1)

    def add(self, i, delta):
        while i < len(self.tree):
            self.tree[i] += delta
            i += i & (-i)

    def query(self, i):
        s = 0
        while i > 0:
            s += self.tree[i]
            i -= i & (-i)
        return s

class Solution:
    def minDeletions(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        A = [ord(c) - ord('A') for c in s]
        bit = FenwickTree(n)
        for i in range(n - 1):
            if A[i] == A[i+1]:
                bit.add(i + 1, 1)

        res = []
        for q in queries:
            if q[0] == 1:
                i = q[1]
                A[i] ^= 1
                if i > 0:
                    bit.add(i, 1 if A[i] == A[i - 1] else -1)
                if i < n - 1:
                    bit.add(i + 1, 1 if A[i] == A[i + 1] else -1)
            else:
                res.append(bit.query(q[2]) - bit.query(q[1]))
        return res