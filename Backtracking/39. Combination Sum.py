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