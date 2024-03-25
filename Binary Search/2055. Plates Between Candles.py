class Solution:
    def platesBetweenCandles(self, s: str, queries: List[List[int]]) -> List[int]:
        A = [i for i,c in enumerate(s) if c == '|']
        res = []
        for a,b in queries:
            i = bisect.bisect_left(A, a)
            j = bisect.bisect(A, b) - 1
            res.append((A[j] - A[i]) - (j - i) if i < j else 0)
        return res