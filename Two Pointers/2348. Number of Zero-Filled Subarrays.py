class Solution:
    def zeroFilledSubarray(self, nums: List[int]) -> int:
        res = 0
        consective = 0
        for i in nums:
            if i != 0: 
                consective = 0
            else:
                consective += 1 
                res += consective
        return res