def minMoves2(self, nums):
    median = sorted(nums)[len(nums) / 2]
    return sum(abs(num - median) for num in nums)

def minMoves2(self, nums):
    nums.sort()
    return sum(nums[~i] - nums[i] for i in range(len(nums) / 2))
