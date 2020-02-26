"""
90. Subsets II

"""
class Solution:
    def subsetsWithDup(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        nums.sort()
        self.res,cur = [], []
        self.backtrack(nums,cur,0)
        return self.res
        
    def backtrack(self,nums, cur, start):
        self.res.append(cur)
        for i in range(start,len(nums)):
            if i!=start and nums[i] == nums[i-1]:
                continue
            self.backtrack(nums,cur+[nums[i]],i+1)



#2020
class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        res = []
        cur = []
        nums.sort()
        def dfs(start):
            if start <= len(nums):
                print(start, cur)
                res.append([i for i in cur])
                for i, v in enumerate(nums[start:], start):
                    cur.append(v)
                    if i == start or nums[i-1] != nums[i]:
                        dfs(i+1)
                    cur.pop()
            
        dfs(0)
        return res

class Solution:
    def subsetsWithDup(self, nums):
        res = [[]]
        nums.sort()
        for i in range(len(nums)):
            start = 0 if nums[i] != nums[i-1] or i == 0 else size
            size = len(res)
            for j in range(start,size):
                res.append(res[j]+[nums[i]])
        return res
