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

# 2020-02-05  
class Solution:
    def combinationSum2(self, cd: List[int], target: int, isStart = True) -> List[List[int]]:
        if isStart:
            cd.sort()
        if target == 0:
            return [[]]
        if target < 0:
            return [] 
        return [[v] + nxt for i, v in enumerate(cd) if i == 0 or cd[i-1] != cd[i] for nxt in self.combinationSum2(cd[i+1:], target - v)]

# 2020-02-05  
class Solution:
    def combinationSum2(self, cd: List[int], target: int) -> List[List[int]]:
        def generate(start, t):
            if t >= 0:
                if t == 0: 
                    yield []
                for i,v  enumerate(cd[start:], start):
                    if i == start or v !=  s[i-1]:
                        for p in generate(i+1, t-v):
                            yield [i] + p 
        return [*generate(0,target)]
