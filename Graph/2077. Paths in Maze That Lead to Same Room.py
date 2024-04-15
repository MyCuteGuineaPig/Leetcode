class Solution:
    def numberOfPaths(self, n: int, corridors: List[List[int]]) -> int:
        al, res = [set() for _ in range(n + 1)], 0
        for (p1, p2) in corridors:
            al[min(p1, p2)].add(max(p1, p2))
        for i in range(n + 1):
            for j in al[i]:
                for k in al[j]:
                    res += 1 if k in al[i] else 0
        return res