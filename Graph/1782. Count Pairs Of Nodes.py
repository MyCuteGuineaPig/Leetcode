class Solution:
    def countPairs(self, n: int, edges: List[List[int]], queries: List[int]) -> List[int]:
        cnt, res = [0] * (n + 1), [0] * len(queries)
        shared = Counter((min(n1, n2), max(n1, n2)) for n1, n2 in edges)
        for n1, n2 in edges:
            cnt[n1] += 1
            cnt[n2] += 1
        sorted_cnt = sorted(cnt)
        print(cnt, sorted_cnt, shared)
        for k, q in enumerate(queries):
            i, j = 1, n 
            while i < j:
                if q < sorted_cnt[i] + sorted_cnt[j]:
                    res[k] += j - i
                    j -= 1
                else:
                    i += 1
            #print(i, j)
            for (i, j), sh_cnt in shared.items():
                if q < cnt[i] + cnt[j] and q + sh_cnt >= cnt[i] + cnt[j]:
                    #这个pair不能算进结果
                    res[k] -= 1;
        return res