class Solution:
    def numTimesAllBlue(self, light: List[int]) -> int:
        m, b = 0, 0
        for c, i in enumerate(light, 1):
            if i > b:
                b = i
            if b == c:
                m += 1        
        return m

class Solution:
    def numTimesAllBlue(self, A):
        right = res = 0
        for i, a in enumerate(A, 1):
            right = max(right, a)
            res += right == i
        return res
