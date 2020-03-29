class Solution:
    def sumFourDivisors(self, nums: List[int]) -> int:
        def f(n):
            cnt =  res = 0
            for i in range(1,int(n**0.5)+1):
                if n % i == 0:
                    cnt += n // i + i
                    res += 1 if n // i == i  else 2
                if res > 4: 
                    return 0
            return cnt if res == 4 else 0
        return sum(f(i) for i in nums)