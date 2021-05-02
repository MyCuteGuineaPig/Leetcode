class Solution:
    def minDominoRotations(self, A: List[int], B: List[int]) -> int:
        for x in [A[0],B[0]]:
            if all(x in d for d in zip(A, B)):
                return len(A) - max(A.count(x), B.count(x))
        return -1
"""
Find intersection set s of all {A[i], B[i]}
s.size = 0, no possible result.
s.size = 1, one and only one result.
s.size = 2, it means all dominoes are [a,b] or [b,a], try either one.
s.size > 2, impossible.
"""
class Solution:
    def minDominoRotations(self, A: List[int], B: List[int]) -> int:
        s = reduce(set.__and__, (set(d) for d in zip(A, B)))
        if not s: return -1
        x = s.pop()
        return min(len(A) - A.count(x), len(B) - B.count(x))