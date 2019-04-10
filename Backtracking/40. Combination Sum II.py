#write by own
class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        def generate(cur, target, start):
            if target == 0:
                yield cur
            if target> 0:
                for i in range(start, len(candidates)):
                    if i == start or candidates[i]!=candidates[i-1]:
                        for p in generate(cur+[candidates[i]], target-candidates[i],i+1):
                            yield p
        candidates.sort()
        return [*generate([], target, 0)]
