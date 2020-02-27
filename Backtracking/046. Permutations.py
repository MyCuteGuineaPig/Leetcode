"""
46. Permutations

Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]

"""

#2019
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        def generate(n):
            if not n:
                return [[]]
            return [[v] + p for i, v in enumerate(n) for p in generate(n[:i]+n[i+1:])]
        return generate(nums)

      
#2019
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        def generate(cur, n):
            if not n:
                yield cur
            for i, v in enumerate(n):
                for p in generate(cur+[v], n[:i]+n[i+1:]):
                    yield p
        return [*generate([],nums)]      

     
#Recursive, take any number as first
class Solution:
    def permute(self, nums):
        return [[n]+p for i,n in enumerate(nums) for p in self.permute(nums[:i]+nums[i+1:])] or [[]]
        

      
      
 #2020
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        return [ x[:i] + [nums[0]] + x[i:] for x in self.permute(nums[1:]) for i in range(len(x)+1) ] if nums else [[]]

#2020
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        def generate(nums):
            if not nums:
                yield []
            else:
                for nxt in self.permute(nums[1:]):
                    for i in range(len(nxt)+1):
                        yield nxt[:i] + [nums[0]] + nxt[i:]
        return [*generate(nums)] 
      
class Solution:
    def permute(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        return (len(nums) and [p[:i] + [nums[0]] + p[i:]
                     for p in self.permute(nums[1:])
                     for i in range(len(nums))]) or [[]]      
      

class Solution:
    def permute(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        return list(itertools.permutations(nums));
        

    def permute(self, nums):
        return map(list, itertools.permutations(nums))

class Solution:
    def permute(self, nums):
        perm = [[]]
        for i in nums:
            newone = []
            for n in perm: 
                for j in range(len(n)+1):
                    newone.append(n[:j]+[i]+n[j:])
            perm = newone
        return perm



class Solution:
    def permute(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        import functools
        return functools.reduce(lambda x, n: [p[:i]+[n]+p[i:] for p in x for i in range(len(p)+1)], nums, [[]])


