class Solution:
    def getXORSum(self, arr1: List[int], arr2: List[int]) -> int:
        a0  = b0 = 0
        for i in arr1:
            a0 = a0 ^ i
        
        for j in arr2:
            b0 = b0 ^ j
        return a0 & b0