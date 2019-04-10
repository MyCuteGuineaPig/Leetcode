"""

47. Permutations II


Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]

"""

class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        def generate(cur, nums):
            if not nums:
                yield cur
            for i, v in enumerate(nums):
                if i == 0 or v != nums[i-1]:
                  for p in generate(cur+[v], nums[:i]+nums[i+1:]):
                    yield p
        nums.sort()
        return [*generate([],nums)]

class Solution:
    def permuteUnique(self, nums):
        ans = [[]]
        for n in nums:
            ans = [ l[:i]+ [n] + l[i:] 
                    for l in ans 
                    for i in range((l+[n]).index(n)+1)]
        return ans;

class Solution:
    def permuteUnique(self, nums):
        import functools
        return functools.reduce(lambda x, y: [p[:i]+[y]+p[i:] for p in x for i in range((p+[y]).index(y)+1) ], nums,[[]])
