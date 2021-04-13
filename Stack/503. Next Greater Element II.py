class Solution:
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        n = len(nums)
        stack, res = [], [-1] * n
        for i in range(len(nums) * 2):
            num = nums[i%n]
            while stack and (nums[stack[-1]] < num):
                res[stack.pop()] = num
            if i < n:
                stack.append(i)
        return res