#write by own
class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        def generate(cur, target, index):
            if target == 0:
                yield cur
            if target > 0:
                for i in range(index, len(candidates)):
                     for p in generate(cur+[candidates[i]],target-candidates[i],i):
                            yield p
        return [*generate([],target,0)];



class Solution(object):
    def combinationSum(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """
        candidates.sort()
        res, cur = [], []
        self.backtracking(candidates,res,cur,target,0)
        return res
    
    def backtracking(self, candidates,res, cur, target, index):
        if target <0: return
        if target == 0: 
            res.append(cur) 
            return
        for i in range(index, len(candidates)):
            self.backtracking(candidates,res,cur+[candidates[i]],target-candidates[i],i)
